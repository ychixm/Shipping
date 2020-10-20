cmake_minimum_required(VERSION 3.17)
project(shipping_Random)

set(CMAKE_CXX_STANDARD 14)

add_executable(shipping_Random main.cpp situation/Point.cpp situation/Point.h situation/Instance.cpp situation/Instance.h situation/Shipping.cpp situation/Shipping.h toolBox/StopWatch.h)