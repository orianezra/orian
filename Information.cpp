//
// Created by orian on 1/13/17.
//
#include "Information.h"
Information::Information() {}

Information::~Information() {}

Information::Information(Tcp* c, TexiCenter *t, int *num) {
    this->texiC = t;
    this->numOfDrivers = num;
    this->tcp = c;
    pthread_mutex_init(&this->list_locker, 0);
    pthread_mutex_init(&this->trips_locker, 0);
}

void Information::setTcp(Tcp *tcp) {
    this->tcp = tcp;
}

Tcp* Information::getTcp(){
    return this->tcp;
}

TexiCenter*  Information::getTexiC(){
    return this->texiC;
}

int*  Information::getNumOfDrivers(){
    return this->numOfDrivers;
}
void Information::addClient(int num) {
    this->clients.push_back(num);
}
void Information::lockList() {
    pthread_mutex_lock(&this->list_locker);
}
void Information::unLockList() {
    pthread_mutex_unlock(&this->list_locker);
}
void Information::lockTrips() {
    pthread_mutex_lock(&this->trips_locker);
}
void Information::unLockTrips() {
    pthread_mutex_unlock(&this->trips_locker);
}