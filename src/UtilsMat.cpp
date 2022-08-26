#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void grayscale(Mat &frame)
{
    int rows = frame.rows;
    int cols = frame.cols;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            Vec3b pixel = frame.at<Vec3b>(i, j);
            int avg = (pixel[0] + pixel[1] + pixel[2]) / 3;
            frame.at<Vec3b>(i, j)[0] = avg;
            frame.at<Vec3b>(i, j)[1] = avg;
            frame.at<Vec3b>(i, j)[2] = avg;
        }
    }
}

void conv(Mat &frame)
{
    int rows = frame.rows;
    int cols = frame.cols;
    Mat frameCopy = frame.clone();
    // convolve the frame
    for (int i = 1; i < rows - 1; i++)
    {
        for (int j = 1; j < cols - 1; j++)
        {
            short int sum = 0;
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    sum += frameCopy.at<uchar>(i + k, j + l);
                }
            }
            frame.at<uchar>(i, j) = sum / 9;
        }
    }
}

bool has_motion(Mat & frame, const Mat & background, const double k)
{
    int rows = frame.rows;
    int cols = frame.cols;

    grayscale(frame);
    conv(frame);

    int numberOfDifferentPixels = 0;

    // count the number of different pixels
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (frame.at<uchar>(i, j) != background.at<uchar>(i, j))
            {
                numberOfDifferentPixels++;
            }
        }
    }
    double perc = (double)numberOfDifferentPixels / (rows * cols);
    return perc > k;
}