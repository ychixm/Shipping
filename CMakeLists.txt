cmake_minimum_required(VERSION 3.17)
project(shipping)

set(CMAKE_CXX_STANDARD 14)

add_executable(shipping main.cpp toolBox/Point.cpp toolBox/Point.h situation/Instance.cpp
        situation/Instance.h situation/Shipping.cpp situation/Shipping.h toolBox/StopWatch.h
        delivery/Truck.cpp
        delivery/Truck.h)