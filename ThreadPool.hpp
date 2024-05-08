#pragma once
#include "TaskQueue.hpp"
#include <thread>
#include <condition_variable>

using threadID = std::thread::id;
using mtx = std::mutex;
using cv = std::condition_variable;
class ThreadPool
{
private:
    TaskQueue taskQueue; // 任务队列
    threadID managerID; // 管理者ID
    threadID workerID; // 工作者ID 
    int minNum; // 最小线程数   
    int maxNum; //最大线程数
    int busyNum; // 忙碌线程数 
    int liveNum; //存活的线程个数
    int exitNum; // 退出的线程个数
    mtx mtxPool; // 锁整个线程池
    // cv notFull; //任务队列是不是满了
    cv notEmpty; //任务队列是不是空了

    bool shutdow; //是否销毁线程池，销毁为true，不销毁为false

public:
    //创建线程池并初始化
    ThreadPool(int min,int max);

    //销毁线程池
    ~ThreadPool();

    //给线程池添加任务
    void addTask(Task task);

    //获取
};