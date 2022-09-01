#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    // Measure avg time it takes to read, grayscale, blur and check motion for each frame
    if (argc != 2)
    {
        cout << "Usage: ./Measurements <video_name>" << endl;
        return -1;
    }
    string videoFile = argv[1];

    // Read the whole video file and compute the time it takes to read a frame.
    auto start = chrono::high_resolution_clock::now();

    VideoCapture cap(videoFile);
    if (!cap.isOpened())
    {
        cout << "Could not open video file " << videoFile << endl;
        return 1;
    }
    Mat frame;
    int frameCount = 0;
    while (cap.read(frame)) {
        frameCount++;
        break;
    }
    auto end = chrono::high_resolution_clock::now();
    auto interarrival_time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Each frame is read in " << interarrival_time.count() / frameCount << " microseconds" << endl;
    cout << "Number of frames: " << frameCount << endl;
    cout << "Total time in seconds: " << interarrival_time.count() / 1000000.0 << endl;

    return 0;
}