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
    map <Driver*, int*> clients;
    pthread_mutex_t trips_locker;
    int* connection;
public:
    Information();
    ~Information();
    Information(Tcp*, TexiCenter*, int*);
    void setTcp(Tcp*);
    Tcp* getTcp();
    TexiCenter* getTexiC();
    int* getNumOfDrivers();
    void addClient(Driver* d , int* num);
    void lockTrips();
    void unLockTrips();
    void setConnection(int*);
    int* getConnection();
    int* getConnOfDriver();
};


#endif //EX3_INFORMATION_H