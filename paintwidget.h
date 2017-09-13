#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>

#include "circle.h"
#include "countingthread.h"


class PaintWidget : public QWidget
{
    Q_OBJECT
private:
    CountingThread MyThread;
    QMutex *mutex;
    std::list<Circle> *list;
    std::list<Circle>::iterator ballIt;
    QTimer *TimerUpdate;
    double updateTime;
    bool left_pressed = false;
public:
    PaintWidget(int obj_num, double updateTimeMs);
    ~PaintWidget();
    void AddRandomBall();
    void AddBallXY(int x, int y);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
};

#endif //PAINTWIDGET_H
