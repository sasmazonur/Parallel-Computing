#!/bin/bash
#SBATCH -J second
#SBATCH -A cs475-575
#SBATCH -p class
#SBATCH --gres=gpu:1
#SBATCH -o second.out
#SBATCH -e second.err
#SBATCH --mail-type=BEGIN,END,FAIL
#SBATCH --mail-user=sasmazo@oregonstate.edu
for nmb in 1024 2048 8192 65536 524288 1048576 2097152 4194304 6291456 8388608
do
  for t in 8 16 32 64 128 256 512
  do
    g++ -DNMB=$nmb -DLOCAL_SIZE=$t -o second second.cpp /usr/local/apps/cuda/cuda-10.1/lib64/libOpenCL.so.1.1 -lm -fopenmp
    ./second >> output2.csv
  done
done
