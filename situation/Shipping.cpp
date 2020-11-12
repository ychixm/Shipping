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

bool Shipping::isDelivered() const {
    return m_delivered;
}

void Shipping::delivered() {
    m_delivered = true;
}

void Shipping::notDelivered() {
    m_delivered = false;
}

double Shipping::getVolume() const {
    return m_volume;
}

void Shipping::setVolume(double volume) {
    m_volume = volume;
}

int Shipping::getOriginWaitingMalus() const {
    return m_originWaitingMalus;
}

void Shipping::setOriginWaitingMalus(int originWaitingMalus) {
    m_originWaitingMalus = originWaitingMalus;
}

int Shipping::getDestinationWaitingMalus() const {
    return m_originWaitingMalus;
}

void Shipping::setDestinationWaitingMalus(int destinationWaitingMalus) {
    m_destinationWaitingMalus = destinationWaitingMalus;
}

Shipping::Shipping(Point &a, Point &b, int ID, std::string &name):m_origin(a),m_destination(b),m_ID(ID),m_name(name){}
Shipping::Shipping(Point &a, Point &b, int ID, std::string &name, int originWaitingMalus, int destinationWaitingMalus,int volume):m_origin(a),m_destination(b),m_ID(ID),m_name(name),m_originWaitingMalus(originWaitingMalus),m_destinationWaitingMalus(destinationWaitingMalus),m_volume(volume){}
Shipping::Shipping(Point a, Point b,int ID,std::string name):m_origin(a),m_destination(b),m_ID(ID),m_name(std::move(name)){}
Shipping::Shipping(Point a, Point b, int ID, std::string name, int originWaitingMalus, int destinationWaitingMalus, int volume):m_origin(a),m_destination(b),m_ID(ID),m_name(std::move(name)),m_originWaitingMalus(originWaitingMalus),m_destinationWaitingMalus(destinationWaitingMalus),m_volume(volume){}

std::ostream &operator<<(std::ostream &os, const Shipping& s) {
    os << s.getName() <<", ID: "<< s.getID() << ", origin: "<< s.getOrigin() <<", malus: "<<s.getOriginWaitingMalus()<<", destination: "<< s.getDestination()<<", malus: "<<s.getDestinationWaitingMalus() << std::endl;
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
