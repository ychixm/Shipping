#ifndef SHIPPING_SERVICE_TRUCK_H
#define SHIPPING_SERVICE_TRUCK_H


#include <vector>
#include <list>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "../toolBox/Point.h"
#include "../situation/Shipping.h"

class Truck {

    private:

    int m_ID;
    float m_distance;
    float m_capacity;
    std::list<int> m_shippingId;
    std::list<Point> m_steps;

    //time start
    //time finish

    public:

    int getID() const;

    void setID(int ID);

    float getDistance() const;

    void setDistance(float distance);

    float getCapacity() const;

    void setCapacity(float capacity);

    const std::list<Point> &getSteps() const;

    void setSteps(const std::list<Point> &steps);

    static std::list<Point> updatedListCopy(std::list<Point> steps, int index, Point ship);
};


#endif //SHIPPING_SERVICE_TRUCK_H
