#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include <iostream>
#include "Truck.h"
#include "../situation/Shipping.h"



class Warehouse
{

    public:
        Warehouse(std::vector<Shipping> shipPoints,int trucks_number);
        void optimizeInsertion();
        bool test_optimizeDistance(const Shipping& shipping);
        int findLowestValue(std::vector<double> tab);
        int smartInsert(int size_of_delivery);

    protected:

    private:
        double m_businessDistance;//it is the sum of the total distance of each truck
        std::vector<Truck> m_trucks_list = std::vector<Truck>();
        std::vector<Shipping> m_deliveryToPlace = std::vector<Shipping>();;
};

#endif // WAREHOUSE_H
