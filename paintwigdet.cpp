#include <paintwidget.h>

PaintWidget::PaintWidget(int obj_num, double updateTimeMs)
{
    updateTime = updateTimeMs;
    ballIt = list.end();
    int i = 0;
    while (i < obj_num)
    {
          QTime timer;
          timer.start ();
          for(;timer.elapsed() < updateTime*5;) {}
          AddRandomBall();
          i++;
    }
    MyThread.SetUpdateTime(updateTime);
    MyThread.SetList(&list);
    MyThread.SetMutex(&mutex);
    MyThread.start();
    connect(&MyThread, SIGNAL(finished()), this, SLOT(update()));
    connect(&timerUpdate, SIGNAL(timeout()), &MyThread, SLOT(TotalCounter()));
    timerUpdate.start(updateTime);
}

void PaintWidget::paintEvent(QPaintEvent * )
{
    mutex.lock();
    QPainter painter(this);
    painter.setBrush(Qt::green);
    std::list<Circle>::iterator it = list.begin();
    while (it != list.end())
    {
        painter.drawEllipse((*it).GetX(), (*it).GetY(), (*it).GetRadius(), (*it).GetRadius());
        ++it;
    }
    mutex.unlock();
}

void PaintWidget::AddRandomBall()
{
    Circle Ball;
    list.push_back(Ball);
    ballIt = list.end();
}

void PaintWidget::mousePressEvent(QMouseEvent * event)
{
    mutex.lock();
    if (event->button() == Qt::RightButton)
    {
        left_pressed = false;
        std::list<Circle>::iterator it = list.begin();
        while (it != list.end())
        {
            if ((abs((*it).GetX() - event->pos().x()) < (*it).GetRadius())
                    && ((abs((*it).GetY() - event->pos().y()) < (*it).GetRadius())))
            {
                list.erase(it);
                ballIt = list.end();
                mutex.unlock();
                return;
            }
            it++;
        }
        QPoint position = event->pos();
        AddBallXY(position.x(), position.y());
    }
    else if (event->button() == Qt::LeftButton)
    {
        left_pressed = true;
        std::list<Circle>::iterator it = list.begin();
        while (it != list.end())
        {
            if ((abs((*it).GetX() - event->pos().x()) < (*it).GetRadius())
                    && ((abs((*it).GetY() - event->pos().y()) < (*it).GetRadius())))
            {
                (*it).LockByMouse(true);
                ballIt = it;
                break;
            }
            ballIt = list.end();
            it++;
        }
    }
    mutex.unlock();
}

void PaintWidget::mouseMoveEvent(QMouseEvent * event)
{
    mutex.lock();
    if (ballIt != list.end() && left_pressed) (*ballIt).SetXY(event->x(), event->y());
    mutex.unlock();
}

void PaintWidget::mouseReleaseEvent(QMouseEvent * event)
{
    mutex.lock();
    if (event->button() == Qt::LeftButton)
    {
        left_pressed = false;
        if (ballIt != list.end())
        {
            (*ballIt).LockByMouse(false);
            ballIt = list.end();
        }
    }
    mutex.unlock();
}


void PaintWidget::AddBallXY(int x, int y)
{
    Circle Ball(x, y);
    list.push_back(Ball);
    ballIt = list.end();
}


