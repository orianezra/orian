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
void Information::addClient(Driver* d , int* num) {
    //this->clients.push_back(num);
    this->clients.insert(std::pair<Driver*,int*>(d,num));
}

void Information::lockTrips() {
    pthread_mutex_lock(&this->trips_locker);
}
void Information::unLockTrips() {
    pthread_mutex_unlock(&this->trips_locker);
}
void Information::setConnection(int* c) {
    this->connection = c;
}
int* Information::getConnection(){
    return this->connection;
}
int* Information::getConnOfDriver() {
    //this->clients
}