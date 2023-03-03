#!/bin/bash

# Compile the C++ program
g++ -std=c++11 1.cpp -o a.o
./a.o
sleep 1
python3 visualise.py
fi