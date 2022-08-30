// Use C++ thread library to develope the parallel version of Sequential.cpp

#include <iostream>
#include <thread>
#include "SharedQueue.cpp"
#include <vector>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <atomic>
#include "OptimizedUtils.cpp"

using namespace std;
using namespace cv;

int runThread(const string videoFilePath, const double k, const int numberOfThreads, const bool pin_threads)
{
    VideoCapture cap(videoFilePath);
    if (!cap.isOpened())
    {
        cout << "Could not open video file " << videoFilePath << endl;
        return 1;
    }

    // Process the background frame
    Mat frame;
    cap.read(frame);
    vector<vector<short int>> background_frame = grayscale(frame);
    background_frame = conv(background_frame);

    atomic<int> numberOfFramesWithMotion(0);

    SharedQueue<Mat> frameQueue;

    auto f = [&]()
    {
        int workerNumberOfFramesWithMotion = 0;
        while (true)
        {
            Mat frame = frameQueue.pop();
            if (frame.empty())
            {
                // update the global variable numberOfFramesWithMotion
                numberOfFramesWithMotion += workerNumberOfFramesWithMotion;
                break;
            }
            if (has_motion(frame, background_frame, k))
            {
                workerNumberOfFramesWithMotion++;
            }
        }
    };

    vector<thread> threads(numberOfThreads);
    for (int i = 0; i < numberOfThreads; i++)
    {
        threads[i] = thread(f);
        // use if-def to pin thread
        if (pin_threads) {
            cpu_set_t cpuset;
            CPU_ZERO(&cpuset);
            CPU_SET(i, &cpuset);
        }   
    }

    // Process the video frames
    while (true)
    {
        Mat frame;
        cap.read(frame);
        if (frame.empty())
        {
            frameQueue.set_finished();
            break;
        }
        frameQueue.push(frame);
    }

    // Wait for all threads to finish
    for (int i = 0; i < numberOfThreads; i++)
    {
        threads[i].join();
    }

    cap.release();
    return numberOfFramesWithMotion;
}