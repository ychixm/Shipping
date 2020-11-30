#include <iostream>
#include "situation/Instance.h"
#include "toolBox/StopWatch.h"
#include "delivery/Truck.h"
#include<random>
#include"delivery/Warehouse.h"
//TODO : add Vehicles

int main() {
    stopwatch<> timer;

    int numberOfShipping = 10;
    int mapSize = 100;
    Instance inst(numberOfShipping,mapSize);

    std::cout << inst << std::endl;

    inst.generateDistanceMatrix();
    inst.showDestinationMatrix();

    Instance::Matrix = inst.getDistanceMatrix();
    std::cout << "time to compute : "<< timer.elapsed_time() << " ms" << std::endl;

    Warehouse warehouse(inst.getShippingPoint(),3);
    warehouse.optimizeInsertion();
    /*Truck truck(inst.getShippingPoint().at(0),4000);
    std::vector<Shipping> m_deliveryToPlace = std::vector<Shipping>();
    std::vector<Shipping> shipPoints = inst.getShippingPoint();
    std::copy(++shipPoints.begin(),shipPoints.end(),std::back_inserter(m_deliveryToPlace));
    //we copy the list of shipping in order to remove a shipping after inserting it in a truck
    while(!m_deliveryToPlace.empty()){
        int index = rand()%m_deliveryToPlace.size();
        std::cout<<""<<std::endl;
        std::cout<<""<<std::endl;
        std::cout<<"colis n°"<<m_deliveryToPlace.at(index).getID()<<std::endl;
        std::cout<< truck.optimize_distance(m_deliveryToPlace.at(index))<<": truck ok?(1=true/0=false)" <<std::endl;
        auto it = m_deliveryToPlace.begin();
        std::advance(it, index);
        m_deliveryToPlace.erase(it);
    }*/
    return 0;
}