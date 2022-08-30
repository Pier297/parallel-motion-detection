#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "../src/Utils.cpp"

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


int main(int argc, char** argv)
{
    // Measure avg time it takes to read, grayscale, blur and check motion for each frame
    if (argc != 3)
    {
        cout << "Usage: ./Measurements <video_name> <kernel_size>" << endl;
        return -1;
    }
    string videoFile = argv[1];
    int kernel_size = atoi(argv[2]);

    // Read the whole video file and compute the time it takes to read a frame.
    auto start = chrono::high_resolution_clock::now();

    auto res = runSequential(videoFile, 0.3, kernel_size);
    int frameCount = 901;
    
    auto end = chrono::high_resolution_clock::now();
    auto interarrival_time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Each frame is read in " << interarrival_time.count() / frameCount << " microseconds" << endl;
    cout << "Number of frames: " << frameCount << endl;
    cout << "Total time in seconds: " << interarrival_time.count() / 1000000.0 << endl;

    return 0;
}