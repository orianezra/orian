
#ifndef EX3_THREADPOOL_H
#define EX3_THREADPOOL_H

#include "Task.h"
#include <queue>
#include <pthread.h>
using namespace std;

class ThreadPool {
private:
    queue<Task *> tasks_queue;
    int threads_num;
    pthread_t* threads;
    bool stop;
    pthread_mutex_t lock;
public:
    ThreadPool(int threads_num);
    ThreadPool(){}
    void doTasks();
    void addTask(Task *task);
    void terminate();
    bool isEmpty();
    virtual ~ThreadPool();
};


#endif //EX3_THREADPOOL_H