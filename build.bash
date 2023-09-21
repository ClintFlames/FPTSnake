#! /env/bash

if [ ! -d "build" ]; then
	mkdir build
fi

cd build

cmake .. -DCMAKE_CXX_COMPILER=g++

cmake --build .