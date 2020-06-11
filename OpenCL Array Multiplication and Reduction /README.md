
1. Multiply two arrays together using OpenCL: D[gid] = A[gid] * B[gid];
2. Multiply two arrays together and add a third using OpenCL: D[gid] = ( A[gid] * B[gid] ) + C[gid];
3. Perform the same array multiply as in #1, but this time with a reduction: Sum = summation{ A[:]

To Run the functions:

./run_first.sh
./run_second.sh
./run_third.sh

Both Runs ins DGX and Rabbit Server. However DGX(submit-*) gives weird output sometime
