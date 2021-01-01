#include <iostream>
#include "situation/Instance.h"
#include "toolBox/StopWatch.h"
#include "delivery/Truck.h"
#include <random>
#include <thread>
#include <utility>
#include"delivery/Warehouse.h"


#define NUMBEROFTRUCKS 3
#define NUMBEROFSHIPPING 10
#define NUMBEROFTHREADS 100

void calculate(std::vector<Shipping> shipPoints,unsigned seed){
    Warehouse warehouse(std::move(shipPoints),NUMBEROFTRUCKS, std::default_random_engine(seed));
    warehouse.switchInsertion();
    warehouse.exportPath(seed);
}

int main() {
    stopwatch<> timer;

    int numberOfShipping = NUMBEROFSHIPPING;
    int mapSize = 100;
    Instance inst(numberOfShipping,mapSize);
    std::cout << inst << std::endl;

    inst.generateDistanceMatrix();
    inst.showDestinationMatrix();
    Truck::Matrix = inst.getDistanceMatrix();


    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::seed_seq seq{seed};
    std::vector<std::uint32_t> seeds(NUMBEROFTHREADS);
    seq.generate(seeds.begin(), seeds.end());

    std::vector<std::thread> threads;


    for(int i =  0; i < NUMBEROFTHREADS; i++) {
        std::thread tmp(calculate, inst.getShippingPoint(), seeds.at(i));
        threads.emplace_back(std::move(tmp));
        //std::cout << std::endl << "start " << i << std::endl;

    }

    for(int i = 0 ; i < NUMBEROFTHREADS; i++){
        threads.at(i).join();
    }
    auto tmp = timer.elapsed_time();
    std::cout <<"time : " << tmp << " ns, " << tmp/(1e9) << " s" << std::endl;
    return 0;
}