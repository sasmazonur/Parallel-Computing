#!/bin/bash
#SBATCH -J third
#SBATCH -A cs475-575
#SBATCH -p class
#SBATCH --gres=gpu:1
#SBATCH -o third.out
#SBATCH -e third.err
#SBATCH --mail-type=BEGIN,END,FAIL
#SBATCH --mail-user=sasmazo@oregonstate.edu
# Try at last 3 different local work sizes, more if you want. Make it no smaller than 32. Make it no larger than 256.
# Vary the size of the input array from 1K to 8M.
for nmb in 1024 2048 8192 65536 524288 1048576 2097152 4194304 6291456 8388608
do
  for t in 32 64 128 256
  do
    g++ -DNMB=$nmb -DLOCAL_SIZE=$t -o third third.cpp /usr/local/apps/cuda/cuda-10.1/lib64/libOpenCL.so.1.1 -lm -fopenmp
    ./third >> output3.csv
  done
done
