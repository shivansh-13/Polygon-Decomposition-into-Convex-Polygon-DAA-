#!/bin/bash

# Compile the C++ program
g++ -std=c++11 1.cpp -o a.o
# g++ -std=c++11 trial.cpp -o a.o
./a.o
python3 visualise.py
# python3 visualise2.py