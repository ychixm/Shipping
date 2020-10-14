#ifndef SHIPPING_SHIPPING_H
#define SHIPPING_SHIPPING_H

#include "Point.h"

class Shipping {
    //TODO : add m^3
private:
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

    friend std::ostream& operator<<(std::ostream& os,const Shipping& s);
    ///the comparison is only on the name of the shipping.
    friend bool operator==(Shipping const& a, Shipping const& b);
};


#endif //SHIPPING_SHIPPING_H
