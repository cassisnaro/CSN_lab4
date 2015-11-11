cmake_minimum_required(VERSION 3.2)
project(CSN_lab4)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES main.cpp SyntacticDependencyTree.cpp SyntacticDependencyTree.h adjacencylist.cpp adjacencylist.h)
add_executable(CSN_lab4 ${SOURCE_FILES})
