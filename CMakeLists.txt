cmake_minimum_required(VERSION 3.12)
project(SimplifiedNAT)

set(CMAKE_CXX_STANDARD 14)

add_executable(SimplifiedNAT main.cpp Address.cpp Address.h NAT.cpp NAT.h Utility.cpp Utility.h)