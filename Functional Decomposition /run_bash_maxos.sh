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
echo "Month,Temp,Precip,Deer,Height,Rabbit" >> output.csv

# number of threads:
g++ project3.cpp -o pro3 -lm -Xpreprocessor -fopenmp -lomp
./pro3 >> output.csv

if [ ! -f "/$FILE" ]; then
    echo "$FILE Succesfully Created!"
fi
