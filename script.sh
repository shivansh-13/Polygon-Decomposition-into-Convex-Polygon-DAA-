#!/bin/bash

# Compile the C++ program
g++ -std=c++11 1.cpp -o a.o
./a.o 25
python3 visualise.py
# python3 visualise2.py