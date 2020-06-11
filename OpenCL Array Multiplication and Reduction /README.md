# OpenCL Array Multiply, Multiply-Add, and Multiply-Reduce
There are many problems in scientific computing where you want to do arithmetic on multiple arrays of numbers (matrix manipulation, Fourier transformation, convolution, etc.). This project is in three parts:
* 1. Multiply two arrays together using OpenCL
* 2. Multiply two arrays together and add a third using OpenCL:
* 3. Perform the same array multiply as in #1, but this time with a reduction


### Data Obtained:
|    cores/trials   |   1      |   10     |   100     |   10000   |   100000   |   1000000   |
|-------------------|----------|----------|-----------|-----------|------------|-------------|
|   1               |   0.89   |   5.12   |   8.26    |   9.93    |   9.9      |   19.01     |
|   2               |   0.52   |   4.31   |   12.87   |   19.94   |   19.81    |   19.79     |
|   4               |   0.36   |   2.98   |   19.47   |   39.3    |   39.22    |   39.38     |
|   8               |   0.31   |   2.66   |   15.63   |   72.69   |   77.92    |   78.8      |


### Array Multiplication Graph 1
<p align="center"><img width=98.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/OpenCL%20Array%20Multiplication%20and%20Reduction%20/images/Pic1.png"></p>

### Array Multiplication Addition 2
<p align="center"><img width=98.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/OpenCL%20Array%20Multiplication%20and%20Reduction%20/images/Pic2.png"></p>

### Findings:
#### What patterns are you seeing in the performance curves?
As we can see from the graph 1.2 and 2.2 above, as array size (num elements) increases also parallel performance increases. But it seems to slow down after certain size. Also, as we can see from graph 1.1 and 2.1, the performance increases as number of work-items per workgroup (local size) increases. However, at the size 128 the performance seems to not increase anymore.
#### Why do you think the patterns look this way? 
CPU cores are designed to minimize latency for a small number of threads at a time each. However, GPU cores are designed to manipulate a large number of concurrent and lightweight threads in order to maximize throughput. For this reason, with OpenCL, we see higher performance output with larger data. Each streaming multiprocessor is only capable of executing simultaneously 32 threads. We have to put at least 32 work items in a workgroup. Otherwise we are not filling up the warp. If data is too small there is not enough time to set the overheads.
#### What is the performance difference between doing a Multiply and doing a Multiply-Add?
For both Multiply and Multiply add we see a similar pattern in performance. However, multiply does overall slightly better job on performance.
#### What does that mean for the proper use of GPU parallel computing?
GPU parallel programing useful for large data computing. However bad for small data sizes.

### Array Multiplication Reduction:
<p align="center"><img width=98.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/OpenCL%20Array%20Multiplication%20and%20Reduction%20/images/Pic3.png"></p>

### Findings:
#### What pattern are you seeing in this performance curve? 
We see a similar pattern to first 2 graphs. As we can see from the graph 3.1 above, as array size (num elements) increases also parallel performance increases. But it seems to slow down after certain size. Also, as we can see from graph 3.2 the performance increases as number of work-items per workgroup (local size) increases. However, at the size 128 the performance seems to not increase anymore.
#### Why do you think the pattern looks this way? 
Since we are not using local work size smaller than 32 and larger than 256. The pattern for Multiply reduction similar to previous array multiply and array multiply addition. Each streaming multiprocessor is only capable of executing simultaneously 32 threads. We have to put at least 32 work items in a workgroup. Otherwise we are not filling up the warp. If data is too small there is not enough time to set the overheads.
#### What does that mean for the proper use of GPU parallel computing? 
GPU parallel programing useful for large data computing. However bad for small data sizes. When we are implementing reduce application. We should make sure that our local work size is reasonable. In this case I used values between 32 and 256.

### How to Run:
To Run the functions:

./run_first.sh
./run_second.sh
./run_third.sh

Both Runs ins DGX and Rabbit Server. However DGX(submit-*) gives weird output sometime

#### Reference:
http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj06.html
