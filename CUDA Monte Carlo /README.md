# CUDA Monte Carlo
This project, will take a scenario and develop a Monte Carlo simulation using CUDA of it, determining how likely a particular output is to happen. Monte Carlo is used to determine the range of outcomes for a series of parameters, each of which has a probability distribution showing how likely each option is to happen.

<p align="center"><img width=90.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/OpenMP%20Monte%20Carlo%20Simulation%20/images/MonteCarloLaser.jpg"></p>

Figure 1. A laser is pointed at a circle (circle, in this case). The circle is defined by a center point (xc,yc) and a radius (r). The beam comes out at a 30° angle. It bounces off the circle. Underneath, even with the laser origin, is an infinite plate.

### Performance Graph
<p align="center"><img width=90.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/CUDA%20Monte%20Carlo%20/images/Picture1.png"></p>

<p align="center"><img width=90.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/CUDA%20Monte%20Carlo%20/images/Picture2.png"></p>

## Table: 
|    BlockSize\NumTrials   |   16000      |   32000       |   64000       |   128000      |   256000      |   512000      |
|--------------------------|--------------|---------------|---------------|---------------|---------------|---------------|
|   16                     |   538.7931   |   945.1796    |   1798.5612   |   2546.149    |   4839.6854   |   5700.0357   |
|   32                     |   538.7931   |   1041.6667   |   1809.9547   |   3460.2077   |   5952.381    |   8134.2142   |
|   64                     |   625        |   998.004     |   2038.7359   |   2791.3469   |   5063.291    |   11049.724   |
|   128                    |   625        |   1210.6537   |   2162.1622   |   3669.7247   |   7299.2703   |   8394.5437   |


### What patterns are you seeing in the performance curves?
As we can see from the graph above, as array size increases performance also increases with GPU parallel computing.
### Why do you think the patterns look this way?
CPU cores are designed to minimize latency for a small number of threads at a time each. However, GPU cores are designed to manipulate a large number of concurrent and lightweight threads in order to maximize throughput.2 For this reason with CUDA, we see higher performance output with larger data.
### Why is a BLOCKSIZE of 16 so much worse than the others?
Each streaming multiprocessor is only capable of executing simultaneously 32 threads. We have to put at least 32 work items in a workgroup. Otherwise we are not filling up the warp.
### How do these performance results compare with what you got in Project #1?
Since we are using GPU parallel computing with DGX server. The performance results from the DGX server is so much higher than OSU1 server.
### What does this mean for the proper use of GPU parallel computing?
GPU parallel programing useful for large data computing. However bad for small data sizes.

#### Reference:
Mike Bailey.(2020) CS475 Project5 Description http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj05.html \
Nvidia. (2020) CUDA C++ Best Practices Guide https://docs.nvidia.com/cuda/cuda-c-best-practices-guide/index.html
