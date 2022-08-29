#pragma once
#include <vector>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<vector<short int>> grayscale(const Mat & frame, const int kernel_size)
{
    int rows = frame.rows;
    int cols = frame.cols;
    // note: we already zero pad the frame so that in the conv we can omit the OOB checks
    int pad = floor(kernel_size / 2);
    vector<vector<short int>> bw_frame(rows + pad*2, vector<short int>(cols + pad*2, 0));
    for (int i = pad; i < rows + pad; i++)
    {
        for (int j = pad; j < cols + pad; j++)
        {
            Vec3b pixel = frame.at<Vec3b>(i - pad, j - pad);
            short int avg = (pixel[0] + pixel[1] + pixel[2]) / 3;
            bw_frame[i][j] = avg;
        }
    }
    return bw_frame;
}

vector<vector<short int>> blur(const vector<vector<short int>> & frame, const int kernel_size)
{
    // note: frame is already zero padded.
    int rows = frame.size();
    int cols = frame[0].size();
    int pad = floor(kernel_size / 2);
    vector<vector<short int>> blurred_frame(rows - 2*pad, vector<short int>(cols - 2*pad));
    // convolve the frame
    for (int i = pad; i < rows - pad; i++)
    {
        for (int j = pad; j < cols - pad; j++)
        {
            short int sum = 0;
            for (int k = -pad; k <= pad; k++)
            {
                for (int l = -pad; l <= pad; l++)
                {
                    sum += frame[i + k][j + l];
                }
            }
            blurred_frame[i - pad][j - pad] = sum / 9;
        }
    }
    return blurred_frame;
}

bool has_motion(const Mat & frame, const vector<vector<short int>> & background, const double k, const int kernel_size)
{
    int rows = frame.rows;
    int cols = frame.cols;

    vector<vector<short int>> processed_frame = grayscale(frame, kernel_size);
    processed_frame = blur(processed_frame, kernel_size);

    int numberOfDifferentPixels = 0;

    // count the number of different pixels
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (processed_frame[i][j] != background[i][j])
            {
                numberOfDifferentPixels++;
            }
        }
    }
    double perc = (double)numberOfDifferentPixels / (rows * cols);
    return perc > k;
}