# OpenMP: Monte Carlo Simulation
This project, will take a scenario and develop a Monte Carlo simulation of it, determining how likely a particular output is to happen. Monte Carlo is used to determine the range of outcomes for a series of parameters, each of which has a probability distribution showing how likely each option is to happen.

<p align="center"><img width=20.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/OpenMP%20Monte%20Carlo%20Simulation%20/images/MonteCarloLaser.jpg"></p>

Figure 1. A laser is pointed at a circle (circle, in this case). The circle is defined by a center point (xc,yc) and a radius (r). The beam comes out at a 30° angle. It bounces off the circle. Underneath, even with the laser origin, is an infinite plate.

### Data Obtained:
|    cores/trials   |   1      |   10     |   100     |   10000   |   100000   |   1000000   |
|-------------------|----------|----------|-----------|-----------|------------|-------------|
|   1               |   0.89   |   5.12   |   8.26    |   9.93    |   9.9      |   19.01     |
|   2               |   0.52   |   4.31   |   12.87   |   19.94   |   19.81    |   19.79     |
|   4               |   0.36   |   2.98   |   19.47   |   39.3    |   39.22    |   39.38     |
|   8               |   0.31   |   2.66   |   15.63   |   72.69   |   77.92    |   78.8      |


### Performance Graph
<p align="center"><img width=20.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/OpenMP%20Monte%20Carlo%20Simulation%20/images/Picture1.png"></p>

<p align="center"><img width=20.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/OpenMP%20Monte%20Carlo%20Simulation%20/images/Picture2.png"></p>

### Findings:
The best performance achieved at 100000 Trials with 8 threads. The probability that the beam hits the plate is 0.13.

### Eight to one thread speedup:
S = 77.92/9.9 \
S = 7.87

### Parallel Fraction For 1-Thread-To-8-Threads Speedup
Fp = (8/7)*( 1- (1 / 7.87) ); \
Fp = 0.9976

To run on Server:
./run_bash_server.sh

To run on MacOS
./run_bash_maxos.sh

It will generate output.csv file with desired outputs. 


Reference:http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj01.html
