#!/bin/bash
g++ -o p7b_openCL p7b_openCL.cpp /usr/local/apps/cuda/cuda-10.1/lib64/libOpenCL.so.1.1 -lm -fopenmp
./p7b_openCL
