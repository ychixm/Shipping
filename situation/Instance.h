#ifndef SHIPPING_INSTANCE_H
#define SHIPPING_INSTANCE_H

#include <chrono>
#include <random>
#include <list>
#include <iostream>
#include <fstream>
#include "Point.h"
#include "Shipping.h"

class Instance {
    std::vector<std::vector<float> > m_distanceMatrix = std::vector<std::vector<float> >();
    std::vector<Shipping> m_shippingPoints = std::vector<Shipping>();
    Point m_depot = Point(0,0);

public:
    const std::vector<std::vector<float>> &getDistanceMatrix() const;

    void setDistanceMatrix(const std::vector<std::vector<float>> &DistanceMatrix);

    const std::vector<Shipping> &getShippingPoint() const;

    void setShippingPoint(const std::vector<Shipping> &ShippingPoint);

    const Point &getDepot() const;

    void setDepot(const Point &Depot);

    void generateDistanceMatrix();

    std::vector<float> calculateDistance(const Shipping& s,char c);

    void showDestinationMatrix();

    void writeTofile(Instance& instance);

    void writeDestiantionTofile(Instance& instance, std::ofstream& write);

public:
    Instance(int &number_of_shipping,int &mapSize);
    friend std::ostream& operator<<(std::ostream& os,const Instance& i);
};

#endif //SHIPPING_INSTANCE_H
