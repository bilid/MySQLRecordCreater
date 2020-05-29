#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <connectionpool.h>
#include <QPushButton>
#include <QDebug>
#include <insertthread.h>
#include <QProgressBar>
#include <QLayout>
#include <QTimer>
#include <mybar.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit_2  ->setDateTime(QDateTime::currentDateTime().addDays(-365*5));
    ui->scrollArea->setStyleSheet("border:0px;background-color:rgba(0,0,0,5);");
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setWidgetResizable(true);
    QGridLayout *pLayout = new QGridLayout(this);//网格布局
    QWidget *contenWidget=new QWidget(ui->scrollArea);
    ui->scrollArea->setWidget(contenWidget);
    contenWidget->setLayout(pLayout);
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        this->kind=ui->kindEdit->text();
        this->ID=ui->IDEdit->text();
        this->address=ui->addressEdit->text();
        this->UPCurrentTime=ui->dateTimeEdit->dateTime() ;
        this->DownCurrentTime=ui->dateTimeEdit_2->dateTime();
        this->HZ=ui->HZEdit->text().toInt();
        this->UP=ui->UPlineEdit->text().toInt();
        this->DOWN=ui->downEdit->text().toInt();
        qDebug()<<kind<<ID<<address<<UPCurrentTime<<DownCurrentTime<<HZ;
        //进度条处理
        MyBar *bar=new MyBar(ui->scrollArea);
        pLayout->addWidget(bar);
        //新建线程处理函数
        InsertThread *insertThread=new InsertThread(0,kind,ID,address,UPCurrentTime,DownCurrentTime,HZ,UP,DOWN);
        //处理进度条函数
        connect(insertThread,&InsertThread::sendProcessingSpeed,[=](float value){
            bar->value=value;
        });
        //定时器处理进程条
        QTimer *timer=new QTimer(this);
        qDebug()<<timer;
        connect(timer,&QTimer::timeout,[=](){
            qDebug()<<timer;
            bar->setValue((int)(bar->value*100)+1);
            if((int)(bar->value*100)+1>=100)
                timer->stop();
        });
        timer->start(10);
        //关闭线程信号
        connect(insertThread,&InsertThread::isDone,[=](){
            insertThread->quit();
            insertThread->wait();
            delete insertThread;


        });

        insertThread->start();
        //connect()

    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
