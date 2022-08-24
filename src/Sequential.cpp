#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include "Utils.cpp"
using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <video file>" << endl;
        return 1;
    }
    string videoFile = argv[1];
    VideoCapture cap(videoFile);
    if (!cap.isOpened())
    {
        cout << "Could not open video file " << videoFile << endl;
        return 1;
    }

    // Process the background frame
    Mat frame;
    cap.read(frame);
    vector<vector<short int>> background_frame = black_and_white(frame);
    background_frame = conv(background_frame);

    // motion is detected if the number of diff pixels is greater than k% of the total number of pixels.
    double k = 0.3;

    // Get the number of frames in the video with opencv
    int numberOfFrames = cap.get(CAP_PROP_FRAME_COUNT);

    int numberOfFramesWithMotion = 0;

    auto start = chrono::high_resolution_clock::now();
    while (cap.read(frame))
    {
        if (has_motion(frame, background_frame, k))
        {
            numberOfFramesWithMotion++;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto interarrival_time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Each frame is processed in " << interarrival_time.count() / numberOfFrames << " microseconds" << endl;
    cout << "Number of frames (minus background): " << numberOfFrames - 1 << endl;
    cout << "Number of frames with motion: " << numberOfFramesWithMotion << endl;
    cout << "Total time in seconds: " << interarrival_time.count() / 1000000.0 << endl;
    return 0;
}