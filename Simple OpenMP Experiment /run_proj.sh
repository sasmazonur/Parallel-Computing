#!/bin/bash

#Check if the files are alread exist in the server
if [[ ! -e /thread_1_output.txt ]]; then
    rm thread_1_output.txt
fi

if [[ ! -e /thread_4_output.txt ]]; then
    rm thread_4_output.txt
fi

# number of threads:
for t in 1 4

do
  echo Thread Number = $t >> thread_$t\_output.txt
  for s in 1
  do
    g++ -DNUMS=$s -D NUMT_FROM_BASH=$t project0.cpp -o prog -lm -fopenmp
    ./prog >> thread_$t\_output.txt
  done
done

if [ ! -f thread_1_output.txt -a ! -f thread_2_output.txt ]; then
   echo "both files not found"
 else
   echo "Files Succesfully Created!"
fi
