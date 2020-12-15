#include <iostream>
#include "situation/Instance.h"
#include "toolBox/StopWatch.h"
#include "delivery/Truck.h"
#include <random>
#include <thread>
#include <mutex>
#include"delivery/Warehouse.h"
//TODO : add Vehicles

std::mutex mtx;

void calculate(const std::vector<Shipping> shipPoints,unsigned seed){
    Warehouse warehouse(shipPoints,3, std::default_random_engine(seed));
    warehouse.switchInsertion();
    warehouse.exportPath(seed);
}

int main() {
    //stopwatch<> timer;

    int numberOfShipping = 10;
    int mapSize = 100;
    Instance inst(numberOfShipping,mapSize);
    std::cout << inst << std::endl;

    inst.generateDistanceMatrix();
    inst.showDestinationMatrix();
    Truck::Matrix = inst.getDistanceMatrix();
    //std::cout << "time to compute : "<< timer.elapsed_time() << " ms" << std::endl;

    Warehouse warehouse(inst.getShippingPoint(),3, std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
    warehouse.switchInsertion();

    //std::thread one(calculate,inst.getShippingPoint(),0);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::seed_seq seq{seed};
    std::vector<std::uint32_t> seeds(20);
    seq.generate(seeds.begin(), seeds.end());

    std::default_random_engine randomEngine(seeds.at(0));
    std::uniform_int_distribution<int> distribution(0,mapSize);
    distribution(randomEngine);


    std::vector<std::thread> threads;
    std::thread tmp(calculate, inst.getShippingPoint(), seeds.at(0));
    tmp.join();

    /*
    for(int i =  0; i < 20; i++) {
        std::thread tmp(calculate, inst.getShippingPoint(), seeds.at(i),*it);
        threads.emplace_back(std::move(tmp));
        std::cout << std::endl << "start " << i << std::endl;
        it++;
    }

    for(int i = 0 ; i < 20 ; i++){
        std::cout << "try join" << std::endl;
        threads.at(i).join();
        std::cout << "success join" << std::endl;
    }


    for(auto resPointer : result){
        std::cout << *resPointer << ", ";
    }*/

    return 0;
}