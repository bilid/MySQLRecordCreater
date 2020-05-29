#ifndef MYBAR_H
#define MYBAR_H

#include <QWidget>
#include <QProgressBar>
class MyBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit MyBar(QWidget *parent = 0);
    float value;
signals:

public slots:
};

#endif // MYBAR_H
