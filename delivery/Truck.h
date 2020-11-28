#ifndef SHIPPING_SERVICE_TRUCK_H
#define SHIPPING_SERVICE_TRUCK_H


#include <vector>
#include <list>
#include<utility>
#include<iterator>
#include<algorithm>
#include "../toolBox/Point.h"
#include "../situation/Shipping.h"

class Truck {

private:

    int m_ID;
    float m_distance;
    float m_capacity;
    std::list<std::pair<Shipping,bool> > m_steps;
    const int INITIAL_CAPACITY = 10;

public:

    int getID() const;

    void setID(int ID);

    float getDistance() const;

    void setDistance(float distance);

    float getCapacity() const;

    void setCapacity(float capacity);

    const std::list<std::pair<Shipping,bool> > &getSteps() const;

    void setSteps(const std::list<std::pair<Shipping,bool> > &steps);

    std::tuple<int,int,double> optimize_distance(Shipping shipping);

    bool insertInTruck(Shipping shipping,double origin,double destination,double distance);

    int findLowestValue(std::vector<double> tab);

    std::pair<int,double> findLowestDistance_andValue(std::vector<double> tab);

    Truck(Shipping shipping, float distance);

    std::pair<int,double> findBestSpot(Shipping shipping, int start , bool origin);

    static std::list<std::pair<Shipping, bool> > updatedListCopy(std::list<std::pair<Shipping, bool> > steps, int index, const Shipping& ship, bool origin);

    static double distanceWithMalus(const std::pair<Shipping,bool>& a, const std::pair<Shipping,bool>& b);

};


#endif //SHIPPING_SERVICE_TRUCK_H
