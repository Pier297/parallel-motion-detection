// Use C++ thread library to develope the parallel version of Sequential.cpp

#include <iostream>
#include <thread>
#include "SharedQueue.cpp"
#include <vector>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <atomic>
using namespace std;
using namespace cv;

vector<float> black_and_white(Mat frame)
{
    // Loop over the pixels and take the RGB values of each pixel and compute the average.
    // Then set the pixel to the average.
    vector<float> bw_frame(frame.rows * frame.cols);
    for (int i = 0; i < frame.rows; i++)
    {
        for (int j = 0; j < frame.cols; j++)
        {
            Vec3b pixel = frame.at<Vec3b>(i, j);
            float average = (pixel[0] + pixel[1] + pixel[2]) / 3;
            bw_frame[i * frame.cols + j] = average;
        }
    }
    return bw_frame;
}

vector<float> conv(vector<float> frame, int rows, int cols)
{
    // blur the frame with a 3x3 kernel.
    // vector is a 1D array representing a 2D array of shape (rows, cols).
    vector<float> blurred_frame(rows * cols);
    for (int i = 1; i < rows - 1; i++)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            float sum = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    sum += frame[(i + k) * cols + j + l];
                }
            }
            blurred_frame[i * cols + j] = sum / 9;
        }
    }
    return blurred_frame;
}

bool has_motion(Mat frame, vector<float> blurred_frame, int rows, int cols, double k)
{
    vector<float> processed_frame = black_and_white(frame);
    processed_frame = conv(processed_frame, rows, cols);
    int numberOfDifferentPixels = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if ((processed_frame[i * cols + j] - blurred_frame[i * cols + j]) != 0)
            {
                numberOfDifferentPixels++;
            }
        }
    }
    double perc = (double)numberOfDifferentPixels / (rows * cols);
    return perc > k;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        cout << "Usage: " << argv[0] << " <video file>"
             << " <number of threads>" << endl;

        cout << "Example: " << argv[0] << " video.mp4 4" << endl;
        return 1;
    }
    string videoFile = argv[1];
    int numberOfThreads = atoi(argv[2]);
    VideoCapture cap(videoFile);
    if (!cap.isOpened())
    {
        cout << "Could not open video file " << videoFile << endl;
        return 1;
    }

    // Process the background frame
    Mat frame;
    cap.read(frame);
    int rows = frame.rows;
    int cols = frame.cols;
    vector<float> background_frame = black_and_white(frame);
    background_frame = conv(background_frame, rows, cols);

    double k = 0.25; // motion is detected if the number of non-zero pixels (i.e. pixels that are not background) is greater than k% of the total number of pixels.

    // Get the number of frames in the video with opencv
    int numberOfFrames = cap.get(CAP_PROP_FRAME_COUNT);

    atomic<int> numberOfFramesWithMotion(0);

    SharedQueue<Mat> frameQueue;

    auto start = chrono::high_resolution_clock::now();

    auto worker = [&]()
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
            if (has_motion(frame, background_frame, rows, cols, k))
            {
                workerNumberOfFramesWithMotion++;
            }
        }
    };

    vector<thread> threads(numberOfThreads);
    for (int i = 0; i < numberOfThreads; i++)
    {
        threads[i] = thread(worker);
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
        frameQueue.push(frame.clone());
    }

    // Wait for all threads to finish
    for (int i = 0; i < numberOfThreads; i++)
    {
        threads[i].join();
    }

    // RES IS 894 for k = 0.3

    auto end = chrono::high_resolution_clock::now();
    auto interarrival_time = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Each frame is processed in " << interarrival_time.count() / numberOfFrames << " microseconds" << endl;
    cout << "Number of frames (minus background): " << numberOfFrames - 1 << endl;
    cout << "Number of frames with motion: " << numberOfFramesWithMotion << endl;
    cout << "Total time in seconds: " << interarrival_time.count() / 1000000.0 << endl;

    cap.release();
    return 0;
}