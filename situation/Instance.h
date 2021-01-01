#ifndef SHIPPING_INSTANCE_H
#define SHIPPING_INSTANCE_H

#include <chrono>
#include <random>
#include <list>
#include <iostream>
#include <fstream>
#include "../toolBox/Point.h"
#include "Shipping.h"

class Instance {
private:
    std::vector<Shipping> m_shippingPoints = std::vector<Shipping>();
    Point m_depot = Point(0,0);
    std::vector<std::vector<double> > m_distanceMatrix = std::vector<std::vector<double> >();

public:
    int m_ID;

    [[nodiscard]] const std::vector<std::vector<double>> &getDistanceMatrix() const;

    void setDistanceMatrix(const std::vector<std::vector<double>> &DistanceMatrix);

    [[nodiscard]] const std::vector<Shipping> &getShippingPoint() const;

    void setShippingPoint(const std::vector<Shipping> &ShippingPoint);

    [[nodiscard]] const Point &getDepot() const;

    void setDepot(const Point &Depot);

    void generateDistanceMatrix();

    std::vector<double> calculateDistance(const Shipping& s,char c);

    void showDestinationMatrix();

     void exportInstances(unsigned seed);

public:
    Instance(int &number_of_shipping,int &mapSize);
    friend std::ostream& operator<<(std::ostream& os,const Instance& i);
};

#endif //SHIPPING_INSTANCE_H
