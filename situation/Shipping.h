#ifndef SHIPPING_SHIPPING_H
#define SHIPPING_SHIPPING_H


#include "Point.h"

class Shipping {
private:
    Shipping(Point a, Point b, std::string &name);

    Point m_origin;
    Point m_destination;
    std::string m_name;
public:

    Shipping(Point &a, Point &b,std::string &name);
    Shipping(Point &a, Point &b);
    Shipping(Point a, Point b,std::string name);
    Shipping(Point a, Point b);


    const Point &getOrigin() const;

    void setOrigin(const Point &Origin);

    const Point &getDestination() const;

    void setDestination(const Point &Destination);

    const std::string &getName() const;

    void setName(const std::string &Name);

    friend std::ostream& operator<<(std::ostream& os,Shipping s);
};


#endif //SHIPPING_SHIPPING_H
