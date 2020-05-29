#ifndef INSERTTHREAD_H
#define INSERTTHREAD_H
#include <QThread>
#include <QObject>
#include<QDateTime>
class InsertThread : public QThread
{
    Q_OBJECT
public:
    explicit InsertThread(QObject *parent ,QString kd,QString id,QString ads,QDateTime upt,QDateTime dct,int hz ,int UP,int DOWM);

signals:
    void sendProcessingSpeed (float i);
    void isDone();
public slots:
protected:
    virtual void run();
private:
    QString kind,ID,address ;
    QDateTime UPCurrentTime ,DownCurrentTime;
    int HZ,UPLINE,DOWNLINE;

};

#endif // INSERTTHREAD_H
