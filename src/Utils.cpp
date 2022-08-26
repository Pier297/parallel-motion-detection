#pragma once
#include <vector>
#include <math.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<vector<short int>> black_and_white(const Mat & frame)
{
    int rows = frame.rows;
    int cols = frame.cols;
    // note: we already zero pad the frame so that in the conv we can omit the OOB checks
    vector<vector<short int>> bw_frame(rows + 2, vector<short int>(cols + 2, 0));
    for (int i = 1; i < rows + 1; i++)
    {
        for (int j = 1; j < cols + 1; j++)
        {
            Vec3b pixel = frame.at<Vec3b>(i - 1, j - 1);
            short int avg = (pixel[0] + pixel[1] + pixel[2]) / 3;
            bw_frame[i][j] = avg;
        }
    }
    return bw_frame;
}

vector<vector<short int>> conv(const vector<vector<short int>> & frame)
{
    // note: frame is already zero padded.
    int rows = frame.size();
    int cols = frame[0].size();
    vector<vector<short int>> blurred_frame(rows - 2, vector<short int>(cols - 2));
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
                    sum += frame[i + k][j + l];
                }
            }
            blurred_frame[i - 1][j - 1] = sum / 9;
        }
    }
    return blurred_frame;
}

bool has_motion(const Mat & frame, const vector<vector<short int>> & background, const double k)
{
    int rows = frame.rows;
    int cols = frame.cols;

    vector<vector<short int>> processed_frame = black_and_white(frame);
    processed_frame = conv(processed_frame);

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