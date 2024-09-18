cmake_minimum_required(VERSION 3.24)
project(OOD_2)

set(CMAKE_CXX_STANDARD 17)

include_directories(part4-5)

add_executable(WeatherStation
        part4-5/main.cpp
        part4-5/Observer.h
        part4-5/WeatherData.h)

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
        part4-5/tests/WeatherTests.cpp
        part4-5/Observer.h
        part4-5/WeatherData.h)

add_executable(WeatherTests1
        part1-3/tests/WeatherTests.cpp
        part1-3/Observer.h
        part1-3/WeatherData.h)


target_link_libraries(WeatherTests gtest gmock gtest_main)
target_link_libraries(WeatherTests1 gtest gmock gtest_main)

add_test(NAME WeatherTests COMMAND WeatherTests)
add_test(NAME WeatherTests1 COMMAND WeatherTests1)