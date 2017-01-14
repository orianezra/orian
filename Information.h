//
// Created by orian on 1/13/17.
//
#ifndef EX3_INFORMATION_H
#define EX3_INFORMATION_H

#include "Tcp.h"
#include "TexiCenter.h"
#include <map>
#include <list>
using namespace std;
class Information {
private:
    Tcp* tcp;
    TexiCenter* texiC;
    int* numOfDrivers;
    list <int> clients;
    pthread_mutex_t list_locker;
    pthread_mutex_t trips_locker;
public:
    Information();
    ~Information();
    Information(Tcp*, TexiCenter*, int*);
    void setTcp(Tcp*);
    Tcp* getTcp();
    TexiCenter* getTexiC();
    int* getNumOfDrivers();
    void addClient(int);
    void lockList();
    void unLockList();
    void lockTrips();
    void unLockTrips();
};


#endif //EX3_INFORMATION_H