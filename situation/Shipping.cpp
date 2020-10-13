#include "Shipping.h"

#include <utility>

const Point &Shipping::getOrigin() const {
    return m_origin;
}

void Shipping::setOrigin(const Point &Origin) {
    m_origin = Origin;
}

const Point &Shipping::getDestination() const {
    return m_destination;
}

void Shipping::setDestination(const Point &Destination) {
    m_destination = Destination;
}

const std::string &Shipping::getName() const {
    return m_name;
}

void Shipping::setName(const std::string &Name) {
    m_name = Name;
}


Shipping::Shipping(Point &a,Point &b):m_origin(a),m_destination(b){}
Shipping::Shipping(Point &a, Point &b, std::string &name):m_origin(a),m_destination(b),m_name(name) {}
Shipping::Shipping(Point a, Point b):m_origin(a),m_destination(b){}
Shipping::Shipping(Point a, Point b, std::string name):m_origin(a),m_destination(b),m_name(std::move(name)) {

}

std::ostream &operator<<(std::ostream &os, Shipping s) {
    os << s.getName() << ", origin: "<< s.getOrigin() <<", destination: "<< s.getDestination() << std::endl;
    return os;
}

bool operator==(Shipping const& a, Shipping const& b) {
    if(a.getName() == b.getName()){
        return true  ;
    }
    else{
        return false;
    }
}
