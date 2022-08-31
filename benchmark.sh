#!/bin/bash

# Check if argument is passed (indicating the number of times to repeat the measurements)
if [ $# -eq 0 ]; then
    echo "No argument supplied. Defaulting to 3 measurements."
    NUM_REPEATS=3
else
    NUM_REPEATS=$1
fi

# <n> <output_path> <pin_threads> <blocking_mode> <video_path_1> <k_1> <res_1> ... <video_path_l> <k_l> <res_l>
# 3x3
# ./bin/Benchmark $NUM_REPEATS "kernel_3x3_00/" 0 0 "videos/small_video.mp4" 0.3 722 "videos/large_video.mp4" 0.3 571
# ./bin/Benchmark $NUM_REPEATS "kernel_3x3_01/" 0 1 "videos/small_video.mp4" 0.3 722 "videos/large_video.mp4" 0.3 571
# ./bin/Benchmark $NUM_REPEATS "kernel_3x3_10/" 1 0 "videos/small_video.mp4" 0.3 722 "videos/large_video.mp4" 0.3 571
# ./bin/Benchmark $NUM_REPEATS "kernel_3x3_11/" 1 1 "videos/small_video.mp4" 0.3 722 "videos/large_video.mp4" 0.3 571

# 9x9 (REMEMBER TO RE-COMPILE)
./bin/Benchmark $NUM_REPEATS "kernel_9x9_00/" 0 0 "videos/small_video.mp4" 0.3 812 "videos/large_video.mp4" 0.3 629
./bin/Benchmark $NUM_REPEATS "kernel_9x9_01/" 0 1 "videos/small_video.mp4" 0.3 812 "videos/large_video.mp4" 0.3 629
./bin/Benchmark $NUM_REPEATS "kernel_9x9_10/" 1 0 "videos/small_video.mp4" 0.3 812 "videos/large_video.mp4" 0.3 629
./bin/Benchmark $NUM_REPEATS "kernel_9x9_11/" 1 1 "videos/small_video.mp4" 0.3 812 "videos/large_video.mp4" 0.3 629