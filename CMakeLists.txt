cmake_minimum_required(VERSION 3.24)
project(OOD_2)

set(CMAKE_CXX_STANDARD 20)


add_executable(WeatherStation
        part7-2/main.cpp
        part7-2/Observer.h
        part7-2/WeatherData.h)

add_executable(WeatherStation7
        part7/main.cpp
        part7/Observer.h
        part7/WeatherData.h)

add_executable(WeatherStation2
        part4-6/main.cpp
        part4-6/Observer.h
        part4-6/WeatherData.h)

add_executable(WeatherStation1
        part1-3/main.cpp
        part1-3/Observer.h
        part1-3/WeatherData.h)

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
        part4-6/tests/WeatherTests.cpp
        part4-6/Observer.h
        part4-6/WeatherData.h)

add_executable(WeatherTests1
        part1-3/tests/WeatherTests.cpp
        part1-3/Observer.h
        part1-3/WeatherData.h)


target_link_libraries(WeatherTests gtest gmock gtest_main)
target_link_libraries(WeatherTests1 gtest gmock gtest_main)

add_test(NAME WeatherTests COMMAND WeatherTests)
add_test(NAME WeatherTests1 COMMAND WeatherTests1)