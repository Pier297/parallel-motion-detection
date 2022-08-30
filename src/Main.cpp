#include "Sequential.cpp"
#include "Thread.cpp"
#include "FastFlow.cpp"
#include "Utimer.cpp"

using namespace std;

int main(int argc, char **argv)
{
    // Usage:
    // Sequential: ./Main -s <video_path> <k> <kernel_size>
    // Thread: ./Main -t <video_path> <k> <num_threads> <kernel_size>
    // Fastflow: ./Main -f <video_path> <k> <num_threads> <kernel_size>
    // Parse the arguments
    // Check if -s or -t or -f was passed
    long time;
    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " -s <video_path> <k>" << endl;
        cout << "Usage: " << argv[0] << " -t <video_path> <k> <num_threads>" << endl;
        cout << "Usage: " << argv[0] << " -f <video_path> <k> <num_threads>" << endl;
        return -1;
    }
    else if (argv[1] == string("-s"))
    {
        if (argc != 4)
        {
            cout << "Usage: " << argv[0] << " -s <video_path> <k>" << endl;
            return -1;
        }
        string video_path = argv[2];
        double k = atof(argv[3]);
        int numberOfFramesWithMotion;
        {
            utimer compute_time("Sequential", &time);
            numberOfFramesWithMotion = runSequential(video_path, k);
        }
        
        cout << "Number of frames with motion: " << numberOfFramesWithMotion << endl;
    }
    else if (argv[1] == string("-t"))
    {
        if (argc != 6)
        {
            cout << "Usage: " << argv[0] << " -t <video_path> <k> <num_threads> <pin_threads>" << endl;
            return -1;
        }
        string video_path = argv[2];
        double k = atof(argv[3]);
        int num_threads = atoi(argv[4]);
        bool pin_threads = atoi(argv[5]);
        int numberOfFramesWithMotion;
        {
            utimer compute_time("Thread", &time);
            numberOfFramesWithMotion = runThread(video_path, k, num_threads, pin_threads);
        }
        cout << "Number of frames with motion: " << numberOfFramesWithMotion << endl;
    }
    else if (argv[1] == string("-f"))
    {
        if (argc != 7)
        {
            cout << "Usage: " << argv[0] << " -f <video_path> <k> <num_threads> <pin_threads> <blocking_mode>" << endl;
            return -1;
        }
        string video_path = argv[2];
        double k = atof(argv[3]);
        int num_threads = atoi(argv[4]);
        bool pin_threads = atoi(argv[5]);
        bool blocking_mode = atoi(argv[6]);
        int numberOfFramesWithMotion;
        {
            utimer compute_time("Fastflow", &time);
            numberOfFramesWithMotion = runFastFlow(video_path, k, num_threads, pin_threads, blocking_mode);
        }
        cout << "Number of frames with motion: " << numberOfFramesWithMotion << endl;
    }
    return 0;
}