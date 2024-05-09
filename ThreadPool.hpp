#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>

class ThreadPool
{
public:
    ThreadPool(int numThreads) : stop(false)
    {
        for (int i = 0; i < numThreads; i++)
        {
            threads.emplace_back([this]()
                                 {
                while (1)
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock,[this](){
                        return stop || !tasks.empty(); //false发生阻塞
                    });
                    if(stop && tasks.empty())
                    {
                        return;
                    }
                    std::function<void()> task(std::move(tasks.front()));
                    tasks.pop();
                    lock.unlock();
                    task();
                } });
        }
    }
    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(mtx);
            stop = true;
        }
        cv.notify_all();
        for (auto &thread : threads)
        {
            thread.join();
        }
    }

    template <class F, class... Args>
    void addTask(F &&f, Args &&...args) // 在template里面，&&是万能引用，左值就是左值，右值就是右值
    {
        std::function<void()> task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(std::move(task));
        }
        cv.notify_one();
    }

private:
    std::vector<std::thread> threads;        // 线程数组
    std::queue<std::function<void()>> tasks; // 任务队列

    std::mutex mtx;
    std::condition_variable cv;

    bool stop;
};


