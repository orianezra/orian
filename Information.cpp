#include "Information.h"
Information::Information() {}

Information::~Information() {}

Information::Information(Tcp* c, TexiCenter *t, int *num) {
    this->texiC = t;
    this->numOfDrivers = num;
    this->tcp = c;
    pthread_mutex_init(&this->trips_locker, 0);
    pthread_mutex_init(&this->driver_locker, 0);
    pthread_mutex_init(&this->client_locker, 0);
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
void Information::addClient(Driver* d , int num) {
    this->clients.insert(std::pair<int,int>(d->getId(),num));
}

pthread_mutex_t* Information::lockTrips() {
    return &this->trips_locker;
}
pthread_mutex_t* Information::lockDriver() {
    return &this->driver_locker;
}
pthread_mutex_t* Information::lockClients() {
    return &this->client_locker;
}
void Information::setConnection(int c) {
    this->connection = c;
}

int Information::getConnection(){
    return this->connection;
}

int Information::getConnOfDriver(Driver *d) {
    return this->clients.find(d->getId())->second;
}
void Information::setTexiC(TexiCenter *t) {
    this->texiC = t;
}