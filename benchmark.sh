#!/bin/bash

# Check if argument is passed (indicating the number of times to repeat the measurements)
if [ $# -eq 0 ]; then
    echo "No argument supplied. Defaulting to 3 measurements."
    NUM_REPEATS=3
else
    NUM_REPEATS=$1
fi

./bin/Benchmark $NUM_REPEATS output/ videos/earth_S.mp4 0.3 607 videos/earth_M.mp4 0.3 546 videos/earth_L.mp4 0.3 472