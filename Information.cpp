#include "Information.h"
//this is the default constructor of the class information
Information::Information() {}

//this is the destructor of the class information
Information::~Information() {}
//this is the constructor of the class information
Information::Information(Tcp* c, TexiCenter *t, int *num) {
    this->texiC = t;
    this->numOfDrivers = num;
    this->tcp = c;
    pthread_mutex_init(&this->trips_locker, 0);
    pthread_mutex_init(&this->driver_locker, 0);
    pthread_mutex_init(&this->client_locker, 0);
}
//a set method for the tcp
void Information::setTcp(Tcp *tcp) {
    this->tcp = tcp;
}
//a get method for the tcp
Tcp* Information::getTcp(){
    return this->tcp;
}
// a get method to the texi center
TexiCenter*  Information::getTexiC(){
    return this->texiC;
}
//a get method for the num of drivers
int*  Information::getNumOfDrivers(){
    return this->numOfDrivers;
}
//a method for adding a client to the mapping between client and connection num
void Information::addClient(Driver* d , int num) {
    this->clients.insert(std::pair<int,int>(d->getId(),num));
}
//a getter method for the trips locker
pthread_mutex_t* Information::lockTrips() {
    return &this->trips_locker;
}
//a getter method for the drivers locker
pthread_mutex_t* Information::lockDriver() {
    return &this->driver_locker;
}
//a getter method for the clients locker
pthread_mutex_t* Information::lockClients() {
    return &this->client_locker;
}
//a setter method for the connection
void Information::setConnection(int c) {
    this->connection.push_back(c);
}
//a getter method for the connection
int Information::getConnection(){
    return this->connection.front();
    this->connection.pop_front();
}
//a getter method for the connection (driver specific)
int Information::getConnOfDriver(Driver *d) {
    return this->clients.find(d->getId())->second;
}
//a setter for texi center
void Information::setTexiC(TexiCenter *t) {
    this->texiC = t;
}
//a method for the finnish flag setting
void Information::finnish(){
    finnishDrive = true;
}
//a method for the finnish flag getting
bool Information::finnishbool() {
    return finnishDrive;
}
