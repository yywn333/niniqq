#include"mthread.h"

ComputeThread::ComputeThread(QObject *parent) :
    QThread(parent)
{
}


void ComputeThread::run()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    qDebug()<<this->currentThreadId();
    //<<:Begin computing!<<endl; >
    computeFinish(222);
}
void ComputeThread::computeFinish(double result)
{
    qDebug()<<result<<endl;
}
