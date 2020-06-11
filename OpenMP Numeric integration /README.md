# OpenMP: Numeric Integration
TUsing OpenMP, compute the super quadric’s total volume by using the given Height function. Super quadric whose equation is x^N+ y^N + z^N = 1. In this assignment, I use parallel reduction to compute the volume of a super quadric using N=4.The tiles in the middle of the floor are full-sized tiles. Tiles along the edges are half-sized. Tiles in the corners are quarter-sized. The volume contribution of each extruded height tile needs to be weighted accordingly. NUMNODES means that there are 4 dots on each side edge.

<p align="center"><img width=99.9% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/OpenMP%20Numeric%20integration%20/images/fig1.png"></p>

Figure 1. A laser is pointed at a circle (circle, in this case). The circle is defined by a center point (xc,yc) and a radius (r). The beam comes out at a 30° angle. It bounces off the circle. Underneath, even with the laser origin, is an infinite plate.

### Data Obtained:
|    cores/Nodes   |   4      |   16     |   32      |   64      |   256    |   1024    |
|------------------|----------|----------|-----------|-----------|----------|-----------|
|   1              |   5.68   |   5.21   |   4.93    |   4.8     |   4.81   |   4.75    |
|   2              |   2.77   |   3.01   |   2.9     |   3.09    |   6.23   |   9.4     |
|   4              |   2.86   |   5.37   |   5.51    |   5.91    |   9.45   |   18.38   |
|   8              |   2.44   |   9.08   |   10.62   |   10.73   |   15     |   36.62   |


### Performance Graph
<p align="center"><img width=90.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/OpenMP%20Numeric%20integration%20/images/Graph1.png"></p>

<p align="center"><img width=95.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/OpenMP%20Numeric%20integration%20/images/Graph2.png"></p>

### Findings:
The best performance achieved at 1024 Nodes with 8 threads. As the number of threads increases, execution time decreases leading to overall performance increase. As we can see the graph above, there is a dramatic increase in 1024 nodes, when we compare 1 thread and 8 threads. From Amdahl's law it follows naturally, that the parallizable part can be executed faster by using more threads. \
If we remove the outlier in the volume data. I think that volume will be 6.3985.

### Speedup:
S = 36.62/4.75 \
S = 7.709

### Parallel Fraction For 1-Thread-To-8-Threads Speedup
Fp = (8/7)*( 1- (1 / 7.709) ); \
Fp = 0.9946

### Maximum speed-up we could ever get:
Max Speed Up we could ever get is 185.

#### How To Run:
To run on Server:
./run_bash_server.sh

To run on MacOS
./run_bash_maxos.sh

It will generate output.csv file with desired outputs. 


Reference:http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj02.html

