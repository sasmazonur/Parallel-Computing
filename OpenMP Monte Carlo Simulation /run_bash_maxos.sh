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
echo "Threads, Trials, Probability, MegaTrialsPerSecond" >> output.csv

# number of threads:
for t in 1 2 4 8

do
  for s in 1 10 100 10000 100000 1000000
  do
    g++ -DNUMTRIALS=$s -DNUMT=$t project1.cpp -o pro1 -lm -Xpreprocessor -fopenmp -lomp
    ./pro1 >> output.csv
  done
done

if [ ! -f "/$FILE" ]; then
    echo "$FILE Succesfully Created!"
fi
