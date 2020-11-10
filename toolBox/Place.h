#include "Point.h"

#ifndef SHIPPING_RANDOM_PLACE_H
#define SHIPPING_RANDOM_PLACE_H


class Place : public Point{
private:
    double m_volume;
    int m_waitingMalus;

public:

    Place(int a, int b , double c , int d);
    Place();

    double getVolume() const;

    void setVolume(double volume);

    int getWaitingMalus() const;

    void setWaitingMalus(int waitingMalus);

    static double distance(Place a, Place b);



};


#endif //SHIPPING_RANDOM_PLACE_H