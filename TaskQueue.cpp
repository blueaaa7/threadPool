#include "TaskQueue.hpp"

TaskQueue::TaskQueue()
{
    mtx.lock();
}


TaskQueue::~TaskQueue()
{
    mtx.unlock();
}

void TaskQueue::addTask(Task task)
{
    mtx.lock();
    {
        taskQueue.push(task);
    }
    mtx.unlock();
}

void TaskQueue::addTask(callback f, void *arg)
{
     mtx.lock();
    {
        taskQueue.emplace(f,arg);
    }
    mtx.unlock();
}

Task TaskQueue::getTask()
{
    Task t;
    int size = getTaskCount();
    if(size > 0)
    {
        mtx.lock();
        t = taskQueue.front();
        taskQueue.pop();
        mtx.unlock();
    }
    return t;
}
