
#ifndef EX3_TASK_H
#define EX3_TASK_H


class Task {
private:
    void *arg;
    void * (*func)(void *arg);
public:
    Task(void * (*func)(void *arg), void* arg);
    Task();
    void execute();
    virtual ~Task();
};

#endif //EX3_TASK_H