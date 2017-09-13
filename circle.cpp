#include "circle.h"

Circle::Circle()
{
    int min = 250;
    int max = 700;
    int randomx;
    int randomy;
    qsrand(QTime::currentTime().msecsSinceStartOfDay());
    randomx = (qrand()) % max + min;
    min = 150;
    max = 450;
    randomy = (qrand()) % max + min;
    x = randomx;
    y = randomy;
}

Circle::Circle(double x, double y) : x(x), y(y) {}

Circle::Circle(double x, double y, double r) : x(x), y(y), radius(r) {}

void Circle::SetXY(double x, double y)
{
    this->x = x;
    this->y = y;
}
double Circle::GetX()
{
    return x;
}
double Circle::GetY()
{
    return y;
}
void Circle::SetRadius(double r)
{
    radius = r;
}
double Circle::GetRadius()
{
    return radius;
}
double Circle::GetSpeedX()
{
    return speedX;
}
double Circle::GetSpeedY()
{
    return speedY;
}
void Circle::SetSpeedXY(double vx, double vy)
{
    speedX = vx;
    speedY = vy;
}
double Circle::GetMass()
{
    return mass;
}

void Circle::SetMass(double m)
{
    mass = m;
}

void Circle::SetForce(double fx, double fy)
{
    forceX = fx;
    forceY = fy;
}

double Circle::GetForceX()
{
    return forceX;
}

double Circle::GetForceY()
{
    return forceY;
}

void Circle::LockByMouse(bool b)
{
    locked = b;
}

bool Circle::IsLockedByMouse()
{
    return locked;
}
