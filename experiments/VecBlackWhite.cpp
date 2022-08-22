// In this experiment we compute the time it takes to read a frame from a video file.
// We use OpenCV to read the video file.
#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
using namespace std;
using namespace cv;

vector<float> black_and_white(Mat frame) {
    // Loop over the pixels and take the RGB values of each pixel and compute the average.
    // Then set the pixel to the average.
    vector<float> bw_frame(frame.rows * frame.cols);
    for (int i = 0; i < frame.rows; i++) {
        for (int j = 0; j < frame.cols; j++) {
            Vec3b pixel = frame.at<Vec3b>(i, j);
            float average = (pixel[0] + pixel[1] + pixel[2]) / 3;
            bw_frame[i * frame.cols + j] = average;
        }
    }
    return bw_frame;
}

int main(int argc, char** argv)
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

    Mat frame;
    int frameCount = 0;
    auto start = chrono::high_resolution_clock::now();
    while (cap.read(frame)) {
        vector<float> bw_frame = black_and_white(frame);
        frameCount++;
    }
    auto end = chrono::high_resolution_clock::now();
    auto interarrival_time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Each frame is read in " << interarrival_time.count() / frameCount << " microseconds" << endl;
    cout << "Number of frames: " << frameCount << endl;
    cout << "Total time in seconds: " << interarrival_time.count() / 1000000.0 << endl;
    return 0;
}