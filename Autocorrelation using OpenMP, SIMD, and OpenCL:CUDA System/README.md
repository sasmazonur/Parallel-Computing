# Autocorrelation using CPU OpenMP, CPU SIMD, and GPU (CUDA/OPENCL)
Autocorrelation, also known as serial correlation, is the correlation of a signal with a delayed copy of itself as a function of delay. Informally, it is the similarity between observations as a function of the time lag between them.

### Autocorrelation Sums[*] vs. shift graph
<p align="center"><img width=95.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/Autocorrelation%20using%20OpenMP%2C%20SIMD%2C%20and%20OpenCL:CUDA%20System/images/scatterplot.png"></p>
As we can see above, the hidden sign wave is about 160 period. At point 164 we see the maxima of 73317.4766.


### Performance Comparison Bar Chart
<p align="center"><img width=99.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/Autocorrelation%20using%20OpenMP%2C%20SIMD%2C%20and%20OpenCL:CUDA%20System/images/BarChart.png"></p>

|            | Performance Mega/Sec |
|------------|----------------------|
|   OMP_1    |   348.736675         |
|   SIMD     |   838.199097         |
|   OMP_8    |   2307.86209         |
|   OpenCL   |   48746.60292        |

#### Findings:
As we can see from the bar chart and table above, OpenCL have the best performance overall. Then OpenMP with 8 thread has the second-best performance, SIMD has the third best performance and OpenMP with 1 thread has the worst performance. OpenCL is 140 times faster when we compare with OpenMP with one thread. As we can see OpenMP with 8 thread is 8 times faster than OpenMP with one thread. I was expecting that SIMD would get higher performance since we are using intel intrinsic. But I think this is due to workload on the rabbit server. In summary, CPU cores are designed to minimize latency for a small number of threads at a time each. However, GPU cores are designed to manipulate a large number of concurrent and lightweight threads in order to maximize throughput. For this reason, with OpenCL, we see highest performance output with large data. In conclusion, GPU parallel programing useful for large data computing. However bad for small data sizes.


#### Reference:
Mike Bailey.(2020) CS475 Project7 Description http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj07.html \
Nvidia. (2020) CUDA C++ Best Practices Guide https://docs.nvidia.com/cuda/cuda-c-best-practices-guide/index.html
