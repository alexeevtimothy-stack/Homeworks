cmake_minimum_required(VERSION 3.15)
project(Calculator)
set(CMAKE_CXX_STANDARD 17)
include_directories(include src)
add_executable(calc src/main.cpp src/PluginManager.cpp src/Calculator.cpp)
set_target_properties(calc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>"
)
add_library(funcln SHARED plugins/funcln.cpp)
add_library(funcsin SHARED plugins/funcsin.cpp)
add_library(funcexp SHARED plugins/funcexp.cpp)
add_library(funcpow SHARED plugins/funcsquare.cpp)
set_target_properties(funcln funcsin funcexp funcpow PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/plugins"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIG>/plugins"
)