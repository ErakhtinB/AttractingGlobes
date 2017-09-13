#ifndef CIRCLE_H
#define CIRCLE_H

#include <QTime>

class Circle
{
public:
    Circle();
    Circle(double x, double y);
    Circle(double x, double y, double r);
    void SetXY(double x, double y);
    double GetX();
    double GetY();
    void SetRadius(double r);
    double GetRadius();
    void SetSpeedXY(double vx, double vy);
    double GetSpeedX();
    double GetSpeedY();
    void SetMass(double m);
    double GetMass();
    void SetForce(double fx, double fy);
    double GetForceX();
    double GetForceY();
    void LockByMouse(bool b);
    bool IsLockedByMouse();
private:
    double x;
    double y;
    double radius = 25;
    double mass = 1000;
    double speedX = 0;
    double speedY = 0;
    double forceX = 0;
    double forceY = 0;
    bool locked = false;
};

#endif // CIRCLE_H
