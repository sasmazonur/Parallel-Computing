#!/bin/bash
#SBATCH -J first
#SBATCH -A cs475-575
#SBATCH -p class
#SBATCH --gres=gpu:1
#SBATCH -o first.out
#SBATCH -e first.err
#SBATCH --mail-type=BEGIN,END,FAIL
#SBATCH --mail-user=sasmazo@oregonstate.edu
#Check if the files are alread exist in the server
for nmb in 1024 2048 8192 65536 524288 1048576 2097152 4194304 6291456 8388608
do
  for t in 8 16 32 64 128 256 512
  do
    g++ -DNMB=$nmb -DLOCAL_SIZE=$t -o first first.cpp /usr/local/apps/cuda/cuda-10.1/lib64/libOpenCL.so.1.1 -lm -fopenmp
    ./first >> output1.csv
  done
done
