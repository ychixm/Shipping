#include <iostream>
#include "situation/Instance.h"

//TODO : add Vehicles

int main() {
    int numberOfShipping = 10;
    int mapSize = 100;
    Instance rand(numberOfShipping,mapSize);
    std::cout << rand << std::endl;
    rand.generateDistanceMatrix();
    rand.showDestinationMatrix();
    return 0;
}
