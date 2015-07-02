#ifndef MTHREAD
#define MTHREAD
#include <qthread>
#include <qdebug>
#include <computethread.h>

class ComputeThread : public QThread
{
    Q_OBJECT
private:
    void run();
public:
    explicit ComputeThread(QObject *parent = 0);

signals:
    void computeFinish(double result);
public slots:

};
#endif // MTHREAD

