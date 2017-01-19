
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
    map <int, int> clients;
    pthread_mutex_t trips_locker;
    pthread_mutex_t client_locker;
    pthread_mutex_t driver_locker;
    int connection;
    bool finnishDrive = false;
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
    void finnish(){
        finnishDrive = true;
    }
    bool finnishbool(){return finnishDrive;}
    int getConnOfDriver(Driver *);
};

#endif //EX3_INFORMATION_H