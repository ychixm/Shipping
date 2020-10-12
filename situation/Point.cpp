
#include "Point.h"

/**
* Calc distance from points coordinates.
*
* @param two Point.
* @return distance between the two points as a float.
*/
 float distance(Point a,Point b){
    return sqrt(pow((b.getX()-a.getX()),2)+pow((b.getY()-a.getY()),2));
}

int Point::getX() const {
    return m_x;
}

void Point::setX(int X) {
    m_x = X;
}

int Point::getY() const {
    return m_y;
}

void Point::setY(int Y) {
    m_y = Y;
}

std::ostream& operator<<(std::ostream& os, Point p){
    os << "x: " << p.getX() << ", y:" << p.getY();
    return os;
}

Point::Point(int &a, int &b):m_x(a),m_y(b) {}
Point::Point(int a, int b):m_x(a),m_y(b) {}
Point::Point():m_x(0),m_y(0){}