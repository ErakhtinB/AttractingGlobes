#ifndef COUNTINGTHREAD_H
#define COUNTINGTHREAD_H

#include <QThread>
#include <cmath>
#include <QMutex>

#include "circle.h"

class CountingThread : public QThread
{
    Q_OBJECT
public:
    void run();
    void SetUpdateTime(double t);
    void SetList(std::list<Circle> *list);
    void SetMutex(QMutex *mutex_thread);
public slots:
    void TotalCounter();
signals:
    void finished();
private:
    std::list<Circle> *list;
    QMutex *mutex;
    double updateTime;
};

#endif // COUNTINGTHREAD_H
