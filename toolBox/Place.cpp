#include "Point.h"
#include "Place.h"

//heritage de point

double Place::distance(Place a, Place b){
    return Point::distance(a,b);
}

//propre à Place

double Place::getVolume() const {
    return m_volume;
}

void Place::setVolume(double volume) {
    m_volume = volume;
}

int Place::getWaitingMalus() const {
    return m_waitingMalus;
}

void Place::setWaitingMalus(int waitingMalus) {
    m_waitingMalus = waitingMalus;
}

Place::Place(int a, int b , double c , int d):Point(a,b),m_volume(c),m_waitingMalus(d) {}
Place::Place():Point(),m_volume(0),m_waitingMalus(0){}