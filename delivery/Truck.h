#ifndef SHIPPING_SERVICE_TRUCK_H
#define SHIPPING_SERVICE_TRUCK_H


#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <utility>
#include "../toolBox/Point.h"
#include "../situation/Shipping.h"

class Truck {

    private:

    int m_ID;
    float m_distance;
    float m_capacity;
    std::list<std::pair<Shipping,bool> > m_steps;

    //time start
    //time finish

    public:

    int getID() const;

    void setID(int ID);

    float getDistance() const;

    void setDistance(float distance);

    float getCapacity() const;

    void setCapacity(float capacity);

    const std::list<std::pair<Shipping,bool> > &getSteps() const;

    void setSteps(const std::list<std::pair<Shipping,bool> > &steps);

    static std::list<std::pair<Shipping,bool> > updatedListCopy(const Truck& truck, int index, const Shipping& ship, bool origin);
};


#endif //SHIPPING_SERVICE_TRUCK_H
