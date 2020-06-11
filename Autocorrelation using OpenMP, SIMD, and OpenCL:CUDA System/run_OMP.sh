#!/bin/bash
# number of threads:
for t in 1 8
do
  g++ -DNUMT=$t -o p7b_OMP p7b_OMP.cpp -lm -fopenmp
  ./p7b_OMP
done
