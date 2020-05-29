#include "insertthread.h"
#include "connectionpool.h"
#include <QDateTime>
#include <QDebug>
InsertThread::InsertThread(QObject *parent, QString kd,QString id,QString ads,QDateTime upt,QDateTime dct,int hz,int UP,int DOWM )
{
    this->kind=kd;
    this->ID=id;
    this->address=ads;
    this->UPCurrentTime=upt;
    this->DownCurrentTime=dct;
    this->HZ=hz;
    this->UPLINE=UP;
    this->DOWNLINE=DOWM;
}

void InsertThread::run()
{
    //获取时间上限与时间下限的差值  单位秒 插入次数
    qint64 timeDiffValue=DownCurrentTime.secsTo(UPCurrentTime);
    if(HZ==0) {
        emit  isDone();
        return;
    }
    qint64 insertDiffValue=3600/HZ;
    qint64 nubOfInst=timeDiffValue/insertDiffValue;
    QSqlDatabase db = ConnectionPool::openConnection();
    QSqlQuery query(db);
    QString qs;//查询语句
    for(qint64 i=0;i<nubOfInst;i++)
    {
        //生成随机数
        qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
        int num = qrand()%(UPLINE-DOWNLINE)+DOWNLINE;
        QString specificTime =DownCurrentTime.addSecs(insertDiffValue*i).toString("yyyy-MM-dd hh:mm:ss");
        qs=QString ("insert into bs(kind,ID,flag,come,time,address) values('%1','%2','c',%3,'%4','%5')").arg( kind).arg(ID ).arg(num).arg(specificTime).arg(address);
        if(!query.exec(qs))qDebug()<<qs;

        emit sendProcessingSpeed((float)i/nubOfInst);

    }

    ConnectionPool::closeConnection(db);
    emit isDone();
}
