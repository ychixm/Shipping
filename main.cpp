#include <iostream>
#include "situation/Instance.h"
#include "toolBox/StopWatch.h"
#include "delivery/Truck.h"

int main() {
    stopwatch<> timer;

    int numberOfShipping = 10;
    int mapSize = 100;
    Instance rand(numberOfShipping,mapSize);

    std::cout << rand << std::endl;

    rand.generateDistanceMatrix();
    rand.showDestinationMatrix();
    rand.writeTofile(rand,"../instances/first.txt");
    std::cout << "time to compute : "<< timer.elapsed_time() << " ms" << std::endl;

    Truck truck(rand.getShippingPoint().at(0),4000);
    for(int index = 1; index < 4 ; index++){
        std::cout<<""<<std::endl;
        std::cout<<""<<std::endl;
        std::cout<<"colis n°"<<index<<std::endl;
        std::cout<< truck.optimize_distance(rand.getShippingPoint().at(index))<<": truck ok?(1=true/0=false)" <<std::endl;
    }
    return 0;
}
