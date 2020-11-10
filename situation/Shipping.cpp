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
int Shipping::getID() const {
    return m_ID;
}

void Shipping::setID(int ID) {
    m_ID = ID;
}

int Shipping::getTruckID() const {
    return m_truckID;
}

void Shipping::setTruckID(int truckID) {
    m_truckID = truckID;
}
bool Shipping::isDelivered() const {
    return m_delivered;
}

void Shipping::delivered() {
    m_delivered = true;
}

void Shipping::notDelivered() {
    m_delivered = false;
}


Shipping::Shipping(Point &a,Point &b):m_origin(a),m_destination(b){
    m_ID = -1;
    m_delivered = false;
    m_truckID = -1;
}
Shipping::Shipping(Point &a, Point &b, std::string &name):m_origin(a),m_destination(b),m_name(name) {
    m_ID = -1;
    m_delivered = false;
    m_truckID = -1;
}
Shipping::Shipping(Point a, Point b):m_origin(a),m_destination(b){
    m_ID = -1;
    m_delivered = false;
    m_truckID = -1;
}
Shipping::Shipping(Point a, Point b, std::string name):m_origin(a),m_destination(b),m_name(std::move(name)){
    m_ID = -1;
    m_delivered = false;
    m_truckID = -1;
}

std::ostream &operator<<(std::ostream &os, const Shipping& s) {
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
