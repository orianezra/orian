
#include "ThreadPool.h"
#include <unistd.h>
#include <iostream>

static void *startTasks(void *arg) {
    ThreadPool *pool = (ThreadPool *)arg;
    pool->doTasks();
    return NULL;
}

//this is the constructor of the ThreadPool class
ThreadPool::ThreadPool(int threads_num) : threads_num(threads_num), stop(false) {
    threads = new pthread_t[threads_num];

    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < threads_num; i++) {
        pthread_create(threads + i, NULL, startTasks, this);
    }
}

//this is method that run on the tasks that thread have to do.
void ThreadPool::doTasks() {
    while (!stop) {
        pthread_mutex_lock(&lock);
        if (!tasks_queue.empty()) {
            Task* task = tasks_queue.front();
            tasks_queue.pop();
            pthread_mutex_unlock(&lock);
            task->execute();
        }
        else {
            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }
    pthread_exit(NULL);
}

//this method add task to the queue.
void ThreadPool::addTask(Task *task) {
    tasks_queue.push(task);
}

//when the prog need to stop, we terminate it by initialized boolean to true.
void ThreadPool::terminate() {
    stop = true;
}

//this is the destructor of the ThreadPool class
ThreadPool::~ThreadPool() {
    delete[] threads;
    pthread_mutex_destroy(&lock);
}

//for new not in use
bool ThreadPool::isEmpty() {
    return tasks_queue.size() == 0;
}