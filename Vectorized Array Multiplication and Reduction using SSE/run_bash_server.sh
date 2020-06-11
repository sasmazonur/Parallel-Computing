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
echo "ArraySize, speedupSIMD, speedupNORM, maxMultiplicationSIMD, maxMultiplicationNORMAL" >> output.csv

# number of threads:
# for t in 1 2 4 8
#
# do
  for s in 10000 50000 100000 800000 1600000 2400000 3200000 5000000 6000000 8000000
  do
    g++ -DARRAYSIZE=$s p4.cpp -o pro4 -lm -fopenmp
    ./pro4 >> output.csv
  done
# done

if [ ! -f "/$FILE" ]; then
    echo "$FILE Succesfully Created!"
fi
