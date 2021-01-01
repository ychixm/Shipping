#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include <iostream>
#include <climits>
#include <unistd.h>
#include "Truck.h"
#include "../situation/Shipping.h"



class Warehouse
{

public:
    Warehouse(std::vector<Shipping> shipPoints,int trucks_number,std::default_random_engine randomEngine);
    void randomInsertion(int truck_id);
    bool test_optimizeDistance(const Shipping& shipping,int truck_id);
    void switchInsertion();
    void smartInsertion();
    int smartFindLowestValue(std::vector<std::pair<double,int>> tab);
    std::vector<Truck> getTrucks_list();
    double getBusinessDistance() const;
    friend std::ostream& operator<<(std::ostream& os,Warehouse w);
    Warehouse();
    void exportPath(unsigned seed);


private:
    double m_businessDistance;//it is the sum of the total distance of each truck
    std::vector<Truck> m_trucks_list = std::vector<Truck>();
    std::vector<Shipping> m_deliveryToPlace = std::vector<Shipping>();
    std::default_random_engine m_randomEngine;
    int m_numberOfTrucksStarted;
};

#endif // WAREHOUSE_H
