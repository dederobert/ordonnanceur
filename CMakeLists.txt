cmake_minimum_required(VERSION 3.9)
project(projet)

set(CMAKE_CXX_STANDARD 11)

file (
        GLOB_RECURSE
        sources
        heuristique/*
        struct/*
        main.cpp
)

add_executable(projet ${sources})