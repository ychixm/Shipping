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