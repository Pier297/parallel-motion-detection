// Use C++ thread library to develope the parallel version of Sequential.cpp

#include <iostream>
#include <vector>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <atomic>
#include "OptimizedUtils.cpp"
#include <ff/ff.hpp>

using namespace std;
using namespace cv;
using namespace ff;

struct Emitter : ff_monode_t<Mat>
{
    VideoCapture cap;
    Emitter(VideoCapture cap) : cap(cap) {}
    Mat *svc(Mat *)
    {
        while (true)
        {
            Mat *frame = new Mat();
            cap.read(*frame);
            if (frame->empty())
            {
                delete frame;
                break;
            }
            ff_send_out(frame);
        }
        return EOS;
    }
};

struct Worker : ff_node_t<Mat, void>
{
    vector<vector<short int>> background_frame;
    double k;
    atomic<int> *numberOfFramesWithMotion;

    int workerNumberOfFramesWithMotion = 0;

    // Base constructor with all global information required to compute the motion frame
    Worker(atomic<int> *numberOfFramesWithMotion, vector<vector<short int>> background_frame, double k)
    {
        this->background_frame = background_frame;
        this->k = k;
        this->numberOfFramesWithMotion = numberOfFramesWithMotion;
    }

    void *svc(Mat *frame)
    {
        if (has_motion(*frame, background_frame, k))
        {
            workerNumberOfFramesWithMotion++;
        }
        delete frame;
        return GO_ON;
    }

    void svc_end()
    {
        numberOfFramesWithMotion->fetch_add(workerNumberOfFramesWithMotion);
    }
};

int runFastFlow(const string videoFilePath, const double k, const int numberOfThreads, const bool pin_threads, const bool blocking_mode)
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

    vector<unique_ptr<ff_node>> workers(numberOfThreads);

    for (int i = 0; i < numberOfThreads; i++)
        workers[i] = make_unique<Worker>(&numberOfFramesWithMotion, background_frame, k);

    ff_Farm<void, void> farm(move(workers), make_unique<Emitter>(cap), nullptr);

    // Enable blocking mode to avoid active waiting
    if (blocking_mode)
    {
        farm.blocking_mode();
    }

    // Disable thread pinning (default)
    if (!pin_threads)
    {
        farm.no_mapping();
    }

    farm.run_and_wait_end();

    return numberOfFramesWithMotion;
}