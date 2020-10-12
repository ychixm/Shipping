#include <math.h>
#include <iostream>
#include <string>
#include <ostream>

#ifndef SHIPPING_POINT_H
#define SHIPPING_POINT_H


class Point {

private:
    int m_x;
    int m_y;

    public:

    Point(int &a, int &b);
    Point(int a, int b);
    Point();

    int getX() const;

    void setX(int X);

    int getY() const;

    void setY(int Y);

    friend std::ostream& operator<<(std::ostream& os,Point p);
};

float distance(Point a,Point b);



#endif //SHIPPING_POINT_H
