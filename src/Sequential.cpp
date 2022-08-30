#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "OptimizedUtils.cpp"
using namespace std;
using namespace cv;

int runSequential(string videoFilePath, double k, const int kernel_size)
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
    vector<vector<short int>> background_frame = grayscale(frame, kernel_size);
    background_frame = blur(background_frame, kernel_size);

    // Process the video
    int numberOfFramesWithMotion = 0;

    while (cap.read(frame))
    {
        if (has_motion(frame, background_frame, k, kernel_size))
        {
            numberOfFramesWithMotion++;
        }
    }

    cap.release();
    return numberOfFramesWithMotion;
}