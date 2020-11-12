#include "Truck.h"

int Truck::getID() const {
    return m_ID;
}

void Truck::setID(int ID) {
    m_ID = ID;
}

float Truck::getDistance() const {
    return m_distance;
}

void Truck::setDistance(float distance) {
    Truck::m_distance = distance;
}

const std::list<std::pair<Shipping,bool> > &Truck::getSteps() const {
    return m_steps;
}

void Truck::setSteps(const std::list<std::pair<Shipping,bool> > &steps) {
    Truck::m_steps = steps;
}

float Truck::getCapacity() const {
    return m_capacity;
}

void Truck::setCapacity(float capacity) {
    m_capacity = capacity;
}

std::list<std::pair<Shipping, bool> > Truck::updatedListCopy(const Truck& truck, int index, const Shipping& ship, bool origin) {
    std::list<std::pair<Shipping, bool> > tmp;
    std::list<std::pair<Shipping, bool> > steps = truck.getSteps();
    std::copy(steps.begin(), steps.end(), std::back_inserter(tmp));
    auto it = tmp.begin();
    std::advance(it, index);
    tmp.insert(it,1,std::pair<Shipping, bool>(ship,origin));
    return tmp;
}