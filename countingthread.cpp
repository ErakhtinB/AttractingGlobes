#include <countingthread.h>
#include <QTimer>
#include <QWidget>
#include <QDebug>

void CountingThread::run()
{

}

void CountingThread::SetUpdateTime(double t)
{
    updateTime = t;
}

void CountingThread::SetList(std::list<Circle> *list)
{
    this->list = list;
}

void CountingThread::SetMutex(QMutex *mutexThread)
{
    mutex = mutexThread;
}

void CountingThread::TotalCounter()
{
    if (!mutex->tryLock(100))
    {
        emit finished();
        return;
    }

    std::list<Circle>::iterator it1 = list->begin();
    while (it1 != list->end())
    {
        double x1 = (*it1).GetX();
        double y1 = (*it1).GetY();
        double r1 = (*it1).GetRadius();
        double m1 = (*it1).GetMass();
        double fx1 = (*it1).GetForceX();
        double fy1 = (*it1).GetForceY();

        std::list<Circle>::iterator it2 = it1;
        std::advance(it2, 1);
        while(it2 != list->end())
        {
            double vx1 = (*it1).GetSpeedX();
            double vy1 = (*it1).GetSpeedY();

            double x2 = (*it2).GetX();
            double y2 = (*it2).GetY();
            double r2 = (*it2).GetRadius();
            double m2 = (*it2).GetMass();
            double vx2 = (*it2).GetSpeedX();
            double vy2 = (*it2).GetSpeedY();
            double fx2 = (*it2).GetForceX();
            double fy2 = (*it2).GetForceY();

            double forceX1 = 0;
            double forceY1 = 0;
            double forceX2 = 0;
            double forceY2 = 0;

            double range = sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1));

            if (range <= (r1 + r2)/2) //Упругий удар
            {

                double v1x = ((m1 - m2) * vx1 + m2 * 2 * vx2)/(m1 + m2);
                double v1y = ((m1 - m2) * vy1 + m2 * 2 * vy2)/(m1 + m2);
                double v2x = ((m2 - m1) * vx2 + m1 * 2 * vx1)/(m1 + m2);
                double v2y = ((m2 - m1) * vy2 + m1 * 2 * vy1)/(m1 + m2);


                (*it1).SetSpeedXY(v1x, v1y);
                (*it2).SetSpeedXY(v2x, v2y);
            }

            double total_force = 1/range - 1/(range * range);


            forceX1 = total_force * (x2 - x1)/range;
            forceY1 = total_force * (y2 - y1)/range;

            forceX2 = -forceX1;
            forceY2 = -forceY1;

            (*it1).SetForce(fx1 + forceX1, fy1 + forceY1);
            (*it2).SetForce(fx2 + forceX2, fy2 + forceY2);

            it2++;
        }
        it1++;
    }

    std::list<Circle>::iterator it3 = list->begin();

    while(it3 != list->end())
    {
        if (!(*it3).IsLockedByMouse())
        {
            double x = (*it3).GetX();
            double y = (*it3).GetY();
            double vx = (*it3).GetSpeedX();
            double vy = (*it3).GetSpeedY();
            double m = (*it3).GetMass();
            double ax = (*it3).GetForceX()/m;
            double ay = (*it3).GetForceY()/m;


            x += vx * updateTime + ax * updateTime * updateTime/2;
            y += vy * updateTime + ay * updateTime * updateTime/2;

            vx += ax * updateTime;
            vy += ay * updateTime;

            (*it3).SetXY(x, y);
            (*it3).SetSpeedXY(vx, vy);
        }
        else
        {
            (*it3).SetSpeedXY(0, 0);
        }
        (*it3).SetForce(0, 0);
        it3++;
    }

    emit finished();
    mutex->unlock();
}
