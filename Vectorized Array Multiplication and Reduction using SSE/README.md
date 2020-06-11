# OpenMP: Monte Carlo Simulation
This project is to test array multiplication/reduction using SIMD and non-SIMD

### Data Obtained:
|    ArraySize   |   SIMD   |   NORMAL   |   maxMultSIMD   |   maxMultNORMAL   |
|----------------|----------|------------|-----------------|-------------------|
|   10000        |   2.55   |   0.39     |   479.02        |   188.18          |
|   50000        |   2.55   |   0.39     |   763.61        |   299.07          |
|   100000       |   2.58   |   0.39     |   311.1         |   120.65          |
|   800000       |   2.45   |   0.41     |   583.65        |   238.48          |
|   1600000      |   2.51   |   0.4      |   584.53        |   232.92          |
|   2400000      |   2.48   |   0.4      |   778.22        |   313.91          |
|   3200000      |   2.47   |   0.41     |   782.61        |   317.14          |
|   5000000      |   2.52   |   0.4      |   949.38        |   377.01          |
|   6000000      |   2.51   |   0.4      |   963.5         |   383.73          |
|   8000000      |   2.51   |   0.4      |   955.47        |   380.52          |


### Performance Graph
<p align="center"><img width=95.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/Vectorized%20Array%20Multiplication%20and%20Reduction%20using%20SSE/images/Picture1.png"></p>

<p align="center"><img width=95.5% src="https://github.com/sasmazonur/Parallel-Computing/blob/master/Vectorized%20Array%20Multiplication%20and%20Reduction%20using%20SSE/images/Picture2.png"></p>

### What patterns are you seeing in the speedups?
For this assignment I used array size between 1000 to 8M. As we can see from graph above speed up is likely to get drop as array size bigger. Its due to temporal cash problem. Where we only using values once, it is possible that speedup multiplication gets head of the ability bring memory from cash. Also, as we can see the speedup get consistent after array size exceed 6M.


Reference:http://web.engr.oregonstate.edu/~mjb/cs575/Projects/proj04.html
