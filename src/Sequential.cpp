#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "Utils.cpp"
using namespace std;
using namespace cv;

int runSequential(string videoFilePath, double k)
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
    vector<vector<short int>> background_frame = black_and_white(frame);
    background_frame = conv(background_frame);

    // Process the video
    int numberOfFramesWithMotion = 0;

    while (cap.read(frame))
    {
        if (has_motion(frame, background_frame, k))
        {
            numberOfFramesWithMotion++;
        }
    }

    cap.release();
    return numberOfFramesWithMotion;
}