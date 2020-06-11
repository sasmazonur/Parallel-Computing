#!/bin/bash
FILE=output.csv

#Check if the files are alread exist in the server
if [[ -f "$FILE" ]]; then
    echo "Removing old $FILE"
    rm $FILE
else
  echo "Loading..."
fi

#Fill the Excel table headers
echo "Threads, Nodes, Volume, MegaHeightsPerSecond" >> output.csv

# number of threads:
for t in 1 2 4 8

do
  for s in 4 16 32 64 256 1024
  do
    g++ -DNUMNODES=$s -DNUMT=$t project2.cpp -o pro1 -lm -fopenmp
    ./pro1 >> output.csv
  done
done

if [ ! -f "/$FILE" ]; then
    echo "$FILE Succesfully Created!"
fi
