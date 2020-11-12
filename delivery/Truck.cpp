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

const std::list<Point> &Truck::getSteps() const {
    return m_steps;
}

void Truck::setSteps(const std::list<Point> &steps) {
    Truck::m_steps = steps;
}

float Truck::getCapacity() const {
    return m_capacity;
}

void Truck::setCapacity(float capacity) {
    m_capacity = capacity;
}

std::list<Point> Truck::updatedListCopy(std::list<Point> steps, int index, Point ship) {
    std::list<Point> tmp;
    std::copy(steps.begin(), steps.end(), std::back_inserter(tmp));
    auto it = steps.begin();
    std::advance(it, index);
    tmp.insert(it,1,ship);
    return std::list<Point>();
}
