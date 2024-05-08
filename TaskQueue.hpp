#pragma once
#include <queue>
#include <mutex>

using callback = void (*)(void *arg);
// 任务结构体
struct Task
{
    Task()
    {
        function = nullptr;
        arg = nullptr;
    }

    Task(callback f, void *arg)
    {
        function = f;
        this->arg = arg;
    }
    callback function;
    void *arg;
};

class TaskQueue
{
private:
    std::queue<Task> taskQueue;
    std::mutex mtx;
    
public:
    TaskQueue();
    
    ~TaskQueue();
    
    //添加任务
    void addTask(Task task);
    void addTask(callback f, void *arg);

    //取出任务
    Task getTask();

    //获取当前任务的个数
   inline int getTaskCount()
   {
    return taskQueue.size();
   }


};