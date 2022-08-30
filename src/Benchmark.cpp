#include "Utimer.cpp"
#include "Sequential.cpp"
#include "Thread.cpp"
#include "FastFlow.cpp"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    if (argc < 8 && (argc % 2 == 1))
    {
        cout << "Usage: " << argv[0] << " <n> <output_path> <pin_threads> <blocking_mode> <video_path_1> <k_1> <res_1> ... <video_path_l> <k_l> <res_l>" << endl;
        cout << "n: number of times to repeat the measurement" << endl;
        cout << "output_path: path to the output measurements file" << endl;
        cout << "video_path_1: path to the first video to be processed" << endl;
        cout << "pin_threads: whether to pin threads to cores" << endl;
        cout << "blocking_mode: whether to use blocking mode in FastFlow" << endl;
        cout << "k_1: k value for the first video" << endl;
        cout << "res_1: result of the first video" << endl;
        cout << "video_path_2: path to the second video to be processed" << endl;
        cout << "k_2: k value for the second video" << endl;
        cout << "res_2: result of the second video" << endl;
        cout << "..." << endl;
        return -1;
    }
    int n = atoi(argv[1]);
    string output_path = argv[2];
    bool pin_threads = atoi(argv[3]);
    bool blocking_mode = atoi(argv[4]);
    int numberOfVideos = (argc - 5) / 3;
    string video_paths[numberOfVideos];
    double ks[numberOfVideos];
    int res[numberOfVideos];
    for (int i = 0; i < numberOfVideos; i++)
    {
        video_paths[i] = argv[5 + i * 3];
        ks[i] = atof(argv[6 + i * 3]);
        res[i] = atoi(argv[7 + i * 3]);
    }
    // check if output directory exists
    if (!std::filesystem::exists(output_path))
    {
        std::filesystem::create_directories(output_path);
    }

    // Sequential benchmark
    long long times[numberOfVideos][n];
    for (int i = 0; i < numberOfVideos; i++)
    {
        for (int j = 0; j < n; j++)
        {
            long time;
            int computedRes;
            {
                utimer compute_time("Sequential", &time);
                computedRes = runSequential(video_paths[i], ks[i]);
            }
            if (computedRes != res[i])
            {
                cout << "Error: result of video " << video_paths[i] << " is " << computedRes << " but should be " << res[i] << endl;
                return -1;
            }
            times[i][j] = time;
        }
    }

    ofstream sequentialFile;
    sequentialFile.open(output_path + "/sequential.csv");
    sequentialFile << "video_path,microseconds" << endl;
    for (int i = 0; i < numberOfVideos; i++)
    {
        sequentialFile << video_paths[i] << ",";
        for (int j = 0; j < n; j++)
        {
            if (j + 1 == n)
            {
                sequentialFile << times[i][j] << endl;
            }
            else
            {
                sequentialFile << times[i][j] << "|";
            }
        }
    }
    sequentialFile.close();

    
    // Thread benchmark
    int numberOfThreads = std::thread::hardware_concurrency() + 2;
    long long timesThread[numberOfVideos][numberOfThreads][n];
    for (int i = 0; i < numberOfVideos; i++)
    {
        for (int j = 1; j <= numberOfThreads; j++)
        {
            for (int k = 0; k < n; k++)
            {
                long time;
                int computedRes;
                {
                    utimer compute_time("Thread", &time);
                    computedRes = runThread(video_paths[i], ks[i], j, pin_threads);
                }
                if (computedRes != res[i])
                {
                    cout << "Error: result of video " << video_paths[i] << " is " << computedRes << " but should be " << res[i] << endl;
                    return -1;
                }
                timesThread[i][j][k] = time;
            }
        }
    }

    ofstream threadFile;
    threadFile.open(output_path + "/thread.csv");
    threadFile << "video_path,threads,microseconds" << endl;
    for (int i = 0; i < numberOfVideos; i++)
    {
        for (int j = 1; j <= numberOfThreads; j++)
        {
            threadFile << video_paths[i] << "," << j << ",";
            for (int k = 0; k < n; k++)
            {
                if (k + 1 == n)
                {
                    threadFile << timesThread[i][j][k] << endl;
                }
                else
                {
                    threadFile << timesThread[i][j][k] << "|";
                }
            }
        }
    }

    // FastFlow benchmark
    long long timesFastFlow[numberOfVideos][numberOfThreads][n];
    for (int i = 0; i < numberOfVideos; i++)
    {
        for (int j = 1; j <= numberOfThreads; j++)
        {
            for (int k = 0; k < n; k++)
            {
                long time;
                int computedRes;
                {
                    utimer compute_time("FastFlow", &time);
                    computedRes = runFastFlow(video_paths[i], ks[i], j, pin_threads, blocking_mode);
                }
                if (computedRes != res[i])
                {
                    cout << "Error: result of video " << video_paths[i] << " is " << computedRes << " but should be " << res[i] << endl;
                    return -1;
                }
                timesFastFlow[i][j][k] = time;
            }
        }
    }

    ofstream ffFile;
    ffFile.open(output_path + "/fastflow.csv");
    ffFile << "video_path,threads,microseconds" << endl;
    for (int i = 0; i < numberOfVideos; i++)
    {
        for (int j = 1; j <= numberOfThreads; j++)
        {
            ffFile << video_paths[i] << "," << j << ",";
            for (int k = 0; k < n; k++)
            {
                if (k + 1 == n)
                {
                    ffFile << timesFastFlow[i][j][k] << endl;
                }
                else
                {
                    ffFile << timesFastFlow[i][j][k] << "|";
                }
            }
        }
    }

    return 0;
}