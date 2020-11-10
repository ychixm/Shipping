#ifndef SHIPPING_SERVICE_TRUCK_H
#define SHIPPING_SERVICE_TRUCK_H


#include <vector>
#include <list>
#include "../toolBox/Point.h"
#include "../situation/Shipping.h"

class Truck {

    private:

    int m_ID;
    float m_distance;
    int m_capacity;
    std::list<int> m_shippingId;
    std::list<Point> m_steps;

    //time start
    //time finish

    public:

    int getID() const;

    void setID(int ID);

    float getDistance() const;

    void setDistance(float distance);

    const std::list<Point> &getSteps() const;

    void setSteps(const std::list<Point> &steps);

    bool isFull();

};


#endif //SHIPPING_SERVICE_TRUCK_H
