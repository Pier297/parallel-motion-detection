# Parallel Motion Detection

## Introduction


## Parallel Strategies

Note: we don't have all the frames in memory at the beginning and so if we want each frame to be processed by a different thread, we need verify that the interarrival time is less than the time it takes to process a frame. Otherwise, there would be no benefit in using multiple threads.

Read takes [2792, 2798, 2782, 2817] microseconds, avg = 2797.25 microseconds

Read + BW takes [3273, 3230, 3373, 3296] microseconds, avg = 3293 microseconds

Read + BW + Conv takes [8730, 8701, 8671, 8750] microseconds, avg = 8713 microseconds


Read takes [2792, 2798, 2782, 2817] microseconds, avg = 2797.25 microseconds
BW takes [481, 432, 591, 479] microseconds, avg = 479.5 microseconds
CONV takes [5437, 5408, 5378, 5457] microseconds, avg = 5420 microseconds

On avg we spend 32% of the time in Read that is not parallizable, thus the max speedup is 1/0.32 = 3.2x.

Remote machine:

Read: 5415
Read + BW: 10474
Read + BW + Conv: 31929


## Maximum Theoretical Speedup

### Amdahl's Law

Max speedup can be computed by applying Amdahl's law.

The serial fraction is given by the time spent reading the video.

This is assuming strong scaling (the video stays the same as more cores are used).

Note that weak scaling does not concern us since we parallelize the processing of frames and so the time spent per frame
is constant regardless of the problem size.

### Work-Span Model

