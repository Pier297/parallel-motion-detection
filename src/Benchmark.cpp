#include "Utimer.cpp"
#include "Sequential.cpp"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
    if (argc < 5 && (argc % 2 == 1))
    {
        cout << "Usage: " << argv[0] << " <n> <output_path> <video_path_1> <k_1> <res_1> ... <video_path_l> <k_l> <res_l>" << endl;
        cout << "n: number of times to repeat the measurement" << endl;
        cout << "output_path: path to the output measurements file" << endl;
        cout << "video_path_1: path to the first video to be processed" << endl;
        cout << "k_1: k value for the first video" << endl;
        cout << "res_1: result of the first video" << endl;
        cout << "video_path_2: path to the second video to be processed" << endl;
        cout << "k_2: k value for the second video" << endl;
        cout << "res_2: result of the second video" << endl;
        cout << "..." << endl;
        // cout << "Example: " << argv[0] << " 3 output/ videos/earth_S.mp4 0.25 videos/earth_M.mp4 0.25 250 videos/earth_L.mp4 0.25 120" << endl;
        return -1;
    }
    int n = atoi(argv[1]);
    string output_path = argv[2];
    int numberOfVideos = (argc - 3) / 3;
    string video_paths[numberOfVideos];
    double ks[numberOfVideos];
    int res[numberOfVideos];
    for (int i = 0; i < numberOfVideos; i++)
    {
        video_paths[i] = argv[3 + i * 3];
        ks[i] = atof(argv[4 + i * 3]);
        res[i] = atoi(argv[5 + i * 3]);
    }

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
    // check if output directory exists
    if (!std::filesystem::exists(output_path))
    {
        std::filesystem::create_directories(output_path);
    }
    sequentialFile.open(output_path + "/sequential.csv");
    sequentialFile << "video_path,k,res,microseconds" << endl;
    for (int i = 0; i < numberOfVideos; i++)
    {
        sequentialFile << video_paths[i] << "," << ks[i] << "," << res[i] << ",";
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

    return 0;
}