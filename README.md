# Parallel Motion Detection

This is a simple motion detection algorithm that uses a parallel approach to count the number of frames that have motion in a video.

For the dependencies, have a look at the 'Dockerfile'.

To Compile run

```bash
$ cmake .
$ make
```

## How to use

You can execute the Main by:

```bash
$ bin/Main -t videos/small_video.mp4 0.3
```

For information see the file 'src/Main.cpp'

## How to Benchmark

After compiling you can run the benchmark by:

```bash
$ ./benchmark.sh
```

## How to change the kernel size

Due to efficiency we fix the kernel size before compiling. To change the kernel size you have to change the value of the macro 'kernel_size' and 'pad' in the file 'src/OptimizedUtils.cpp' and recompile the project.

## Project Structure

The project is structured as follows:

- src: Contains the source code
- experiments: Contains the source code for the experiments (i.e. the timings of the different operations)
- videos: Contains the videos used for the experiments
- benchmark.sh: Script to run the benchmark
- Dockerfile: Dockerfile to build the project
- CMakeLists.txt: CMake file to build the project

Note, in src/ we have Utils.cpp and OptimizedUtils.cpp, they differs on the way they compute the convolution. The first one uses a naive approach, while the second one uses a more optimized approach that exploits vectorization.