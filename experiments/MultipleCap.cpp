// In this experiment we compute the time it takes to read a frame from a video file.
// We use OpenCV to read the video file.
#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <video file>" << endl;
        return 1;
    }
    string videoFile = argv[1];
    VideoCapture cap1(videoFile);
    VideoCapture cap2(videoFile);
    if (!cap1.isOpened() || !cap2.isOpened())
    {
        cout << "Could not open video file " << videoFile << endl;
        return 1;
    }
    // seek cap2 to the middle of the video
    cap2.set(CAP_PROP_POS_FRAMES, cap2.get(CAP_PROP_FRAME_COUNT) / 2);
    // Read the whole video file and compute the time it takes to read a frame.
    auto start = chrono::high_resolution_clock::now();
    Mat frame1;
    Mat frame2;
    int frameCount = 0;
    int i = 0;
    bool finishedCap2 = false;
    while (true) {
        if (finishedCap2 && i == (cap2.get(CAP_PROP_FRAME_COUNT) / 2)) {
            break;
        }
        if (!finishedCap2) {
            cap2.read(frame2);
            if (frame2.empty()) {
                finishedCap2 = true;
            }
            frameCount++;
        }
        if (i < (cap2.get(CAP_PROP_FRAME_COUNT) / 2)) {
            cap1.read(frame1);
            i++;
            frameCount++;
        }
        cout << i << " " << frameCount << endl;
    }
    auto end = chrono::high_resolution_clock::now();
    auto interarrival_time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Each frame is read in " << interarrival_time.count() / frameCount << " microseconds" << endl;
    cout << "Number of frames: " << frameCount << endl;
    cout << "Total time in seconds: " << interarrival_time.count() / 1000000.0 << endl;
    return 0;
}