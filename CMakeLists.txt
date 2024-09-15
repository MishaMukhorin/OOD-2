cmake_minimum_required(VERSION 3.24)
project(OOD_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(part1)

add_executable(WeatherStation
        part1/main.cpp
        part1/Observer.h
        part1/WeatherData.h)

# Enable testing
enable_testing()

# Fetch GoogleTest and GoogleMock
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(WeatherTests
        part1/tests/WeatherTests.cpp
        part1/Observer.h
        part1/WeatherData.h)



