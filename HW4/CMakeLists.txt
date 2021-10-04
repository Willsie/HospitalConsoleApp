cmake_minimum_required(VERSION 3.19)
project(hw4)

set(CMAKE_CXX_STANDARD 14)

add_executable(hw4 main.cpp HospitalMethods.cpp Patient.cpp Patient.h CompareByPriority.cpp Logger.cpp Logger.h User.cpp User.h)

