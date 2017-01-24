
#ifndef EX3_INFORMATION_H
#define EX3_INFORMATION_H
#include "Tcp.h"
#include "TexiCenter.h"
#include <map>
#include <list>
using namespace std;
//this class's purpose is to manage an information object in order to pass it to threads
//it contains the texi center, num of drivers and tcp object
class Information {
private:
    Tcp* tcp;
    TexiCenter* texiC;
    int* numOfDrivers;
    map <int, int> clients;
    pthread_mutex_t trips_locker;
    pthread_mutex_t client_locker;
    pthread_mutex_t driver_locker;
    list<int> connection;
    bool finnishDrive;
public:
    Information();
    ~Information();
    Information(Tcp*, TexiCenter*, int*);
    void setTcp(Tcp*);
    Tcp* getTcp();
    void setTexiC(TexiCenter *);
    TexiCenter* getTexiC();
    int* getNumOfDrivers();
    void addClient(Driver* d , int num);
    pthread_mutex_t* lockTrips();
    pthread_mutex_t* lockDriver();
    pthread_mutex_t* lockClients();
    void setConnection(int);
    int getConnection();
    void finnish();
    bool finnishbool();
    int getConnOfDriver(Driver *);
};

#endif //EX3_INFORMATION_H