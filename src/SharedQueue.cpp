#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

template <typename T>
class SharedQueue
{
public:
    SharedQueue() {}
    ~SharedQueue() {}

    void push(T value)
    {
        // lock the mutex to prevent other threads from accessing the queue while we are adding a value to it.
        unique_lock<mutex> lock(mutex_);
        queue_.push(value);
        // notify one thread that there is a new value in the queue.
        condition_.notify_one();
    }
    T pop()
    {
        unique_lock<mutex> lock(mutex_);
        while (queue_.empty() && !finished)
        {
            // wait for a value to be pushed to the queue.
            condition_.wait(lock);
        }
        // if the finished_flag is set to true and the queue is empty, return an empty T.
        if (finished && queue_.empty())
        {
            return T();
        }
        else
        {
            // otherwise, return the value at the front of the queue_.
            T value = queue_.front();
            queue_.pop();
            return value;
        }
    }
    void set_finished()
    {
        unique_lock<mutex> lock(mutex_);
        finished = true;
        condition_.notify_all();
    }

private:
    queue<T> queue_;
    mutex mutex_;
    condition_variable condition_;
    bool finished = false;
};