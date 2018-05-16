cmake_minimum_required(VERSION 3.9)
project(projet)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        struct
        ./
)

file (
        GLOB_RECURSE
        sources
        heuristique/*
        genetique/*
        struct/*
        main.cpp
        Utils.hpp
)

add_executable(projet ${sources})