cmake_minimum_required(VERSION 3.24)
project(OOD_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(part1)

add_executable(WeatherStation
        part1/main.cpp
        part1/Observer.h
        part1/WeatherData.h)
