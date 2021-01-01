#ifndef SHIPPING_SERVICE_TRUCK_H
#define SHIPPING_SERVICE_TRUCK_H


#include <mutex>
#include <vector>
#include <list>
#include<utility>
#include<iterator>
#include<algorithm>
#include <iostream>
#include <random>
#include<fstream>
#include "../toolBox/Point.h"
#include "../situation/Shipping.h"

class Truck {

private:

    int m_ID;
    double m_distance;
    double m_capacity;
    std::list<std::pair<Shipping,bool> > m_steps;
    const int INITIAL_CAPACITY = 10;

public:

    static std::vector<std::vector<double> > Matrix;

    Truck(const Shipping& shipping, int id);

    int getID() const;

    void setID(int ID);

    double getDistance() const;

    void setDistance(double distance);

    double getCapacity() const;

    void setCapacity(double capacity);

    const std::list<std::pair<Shipping,bool> > &getSteps() const;

    void setSteps(const std::list<std::pair<Shipping,bool> > &steps);

    std::tuple<int,int,double> optimize_distance(const Shipping& shipping,std::default_random_engine randomEngine);

    bool insertInTruck(const Shipping& shipping,double origin,double destination,double distance);

    std::pair<int,double> randomLowestValue(std::vector<double> tab,std::default_random_engine randomEngine);

    std::pair<int,double> findBestSpot(const Shipping& shipping, int start , bool origin,std::default_random_engine randomEngine);

    static std::list<std::pair<Shipping, bool> > updatedListCopy(std::list<std::pair<Shipping, bool> > steps, int index, const Shipping& ship, bool origin);

    static double distanceWithMalus(const std::pair<Shipping,bool>& a, const std::pair<Shipping,bool>& b);

    static std::default_random_engine randomEngine;

    Point getBarycentre();
};


#endif //SHIPPING_SERVICE_TRUCK_H