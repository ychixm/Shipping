#include <iostream>
#include "situation/Instance.h"
#include "toolBox/StopWatch.h"
//TODO : add Vehicles

int main() {
    stopwatch<> timer;

    int numberOfShipping = 10;
    int mapSize = 100;
    Instance rand(numberOfShipping,mapSize);

    std::cout << rand << std::endl;

    rand.generateDistanceMatrix();
    rand.showDestinationMatrix();
    rand.writeTofile(rand);
    std::cout << "time to compute : "<< timer.elapsed_time() << " ms" << std::endl;

    return 0;
}