#ifndef SHIPPING_INSTANCE_H
#define SHIPPING_INSTANCE_H

#include <chrono>
#include <random>
#include <list>
#include <iostream>
#include "Point.h"
#include "Shipping.h"


class Instance {
    std::list<std::list<float> > m_distanceMatrix = std::list<std::list<float> >();
    std::list<Shipping> m_shippingPoints = std::list<Shipping>();
    Point m_depot = Point(0,0);

public:
    const std::list<std::list<float>> &getDistanceMatrix() const;

    void setDistanceMatrix(const std::list<std::list<float>> &DistanceMatrix);

    const std::list<Shipping> &getShippingPoint() const;

    void setShippingPoint(const std::list<Shipping> &ShippingPoint);

    const Point &getDepot() const;

    void setDepot(const Point &Depot);

    void generateDistanceMatrix();

    std::list<float> calculateDistance(const Shipping& s,char c);

    void showDestinationMatrix();

public:
    Instance(int &number_of_shipping,int &mapSize);
    friend std::ostream& operator<<(std::ostream& os,const Instance& i);
};


#endif //SHIPPING_INSTANCE_H
