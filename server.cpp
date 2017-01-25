#include "Tcp.h"
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include "Grid.h"
#include "Map.h"
#include "TexiCenter.h"
#include "Information.h"
#include <mutex>
#include "pthread.h"
#include <boost/cast.hpp>
#include <boost/serialization/list.hpp>

using namespace std;
//using namespace boost;
void* createClientCon(void*);
void* managerClient(void*);
void* calculateWay(void*);
map <int, int> options;
int main(int argc, char *argv[]) {
    Information *in;

    Tcp* tcp = new Tcp(1, atoi(argv[1]));
    tcp->initialize();
    int i, j, pOfAbs;
    char damy;
    long time = 0;
    cin >> i >> j;
    Grid *gDummy2;
    Driver dDummy;
    TripInfo *tIDummy;
    pthread_t tTrip;
    pthread_t t1;
    Grid *g = new Grid(i, j);
    Map *m = new Map(g);
    TexiCenter *texiC = new TexiCenter();

    cin >> pOfAbs;
    if (pOfAbs > 0) {
        int arr[2];
        while (pOfAbs > 0) {
            cin >> arr[0] >> damy >> arr[1];
            m->createO(Point(arr[0], arr[1]));
            pOfAbs--;

        }
    }
    texiC->setMap(m);
    do {
        int id, age, exp, vId, startX, startY, endX, endY, numOfPs, type;
        double tariff;
        char ch;
        char status;
        char ch2;

        MaterialStatus mS;
        CarColors color;

        CarsManufactor cMF;
        cin >> i;
        switch (i) {
            case 1: {
                //create drivers
                int numOfDrivers;
                cin >> numOfDrivers;

                int *num = new int(numOfDrivers);
                in = new Information(tcp, texiC, num);
                int status = pthread_create(&t1, NULL, createClientCon, (void *) in);
                pthread_join(t1, NULL);
                //pthread_detach(t1);
                break;
            }
            case 2: {
                unsigned long timeOfTrip;
                cin >> id >> damy >> startX >> damy >> startY >> damy
                    >> endX >> damy >> endY >> damy >> numOfPs >> damy >> tariff >> damy >> timeOfTrip;
                tIDummy = new TripInfo(0, numOfPs, id, tariff,
                                       new Point(startX, startY), new Point(endX, endY), timeOfTrip);
                texiC->setTripI(tIDummy);
                int *num = new int(texiC->getListTrips().size());
                Information *inf = new Information(tcp, texiC, num);
                int statusT = pthread_create(&tTrip, NULL, calculateWay, (void *) inf);
                pthread_join(tTrip, NULL);
                break;
            }
            case 3: {
                cin >> id >> damy >> type >> damy >> ch >> damy >> ch2;
                switch (ch) {
                    case 'H': {
                        cMF = CarsManufactor::HONDA;
                        break;
                    }
                    case 'F': {
                        cMF = CarsManufactor::FIAT;
                        break;
                    }
                    case 'S': {
                        cMF = CarsManufactor::SUBARO;
                        break;
                    }
                    case 'T': {
                        cMF = CarsManufactor::TESLA;
                        break;
                    }
                    default: {
                        cout << "type not exist" << endl;
                        break;
                    }
                }
                switch (ch2) {
                    case 'B': {
                        color = CarColors::BLUE;
                        break;
                    }
                    case 'R': {
                        color = CarColors::RED;
                        break;
                    }
                    case 'G': {
                        color = CarColors::GREEN;
                        break;
                    }
                    case 'W': {
                        color = CarColors::WHITE;
                        break;
                    }
                    case 'P': {
                        color = CarColors::PINK;
                        break;
                    }
                    default: {
                        cout << "color not exist" << endl;
                        break;
                    }
                }
                switch (type) {
                    case 1: {
                        Cab *cabDummy = new Cab(id, 0, 0, color, cMF);
                        texiC->setVehicleCab(cabDummy);
                        break;
                    }
                    case 2: {
                        LuxuryCab *cabDummy = new LuxuryCab(id, 0, 0, color, cMF);
                        texiC->setVehicleCab(cabDummy);

                        break;
                    }
                    default: {
                        cout << "cab not exist" << endl;
                        break;
                    }
                }
                break;
            }
            case 4: {
                cin >> id;
                if (texiC->getDriver(id) != NULL) {
                    int z = texiC->getDriver(id)->getLocation().getX_axis();
                    int v = texiC->getDriver(id)->getLocation().getY_axis();
                    cout << "(" << z << "," << v << ")" << endl;
                } else {
                    cout << "driver does not exist in the system" << endl;
                }
                break;
            }
            case 6: {
            }
            case 9: {//need to get out
                cout << "yeahhh" << endl;
                TripInfo *t;
                int sizeLDriver = texiC->getListDriver().size();
                //loop over the trips, check if its the time
                for (int j = 0; j < sizeLDriver; j++) {
                    Driver *d = texiC->getListDriver().front();
                    texiC->getListDriver().pop_front();
                    tcp->setClient(in->getConnOfDriver(d));
                    if (!d->ifHasTrip()) {
                        int sizeTList = texiC->getListTrips().size();
                        for (int i = 0; i < sizeTList; i++) {
                            t = texiC->getListTrips().front();
                            texiC->getListTrips().pop_front();
                            if (time == t->getTimeOfTrip()) {
                                sleep(1);
                                tcp->sendData("start triping shimi");

                                sleep(1);
                                t->save();
                                d->setTripInfo(t);
                                tcp->sendData(d->getTripInfo()->serial_str);
                                d->setHasTrip(true);
                                t->getWay().pop_front();
                                texiC->upData(d);
                                continue;
                            } else if (time < t->getTimeOfTrip()) {
                                texiC->getListTrips().push_back(t);
                                sleep(1);
                                tcp->sendData("you can`t drive :(");
                                //break;
                            }
                        }
                    } else {
                        sleep(1);
                        tcp->sendData("you can drive :)");

                        char buffer0[2000];
                        tcp->reciveData(buffer0, sizeof(buffer0));

                        string stMessage(buffer0);
                        //in->getTexiC()->upData(d);
                        if (stMessage.compare("drive one step") == 0) {
                            in->getTexiC()->upData(d);
                            if (d->getTripInfo()->getWay().size() == 0) {
                                sleep(1);
                                tcp->sendData("end of trip");
                                d->setHasTrip(false);
                            }
                        }

                    }
                    texiC->getListDriver().push_back(d);
                }
                time++;
                break;
            }
        }
    }
    while (i != 7);
    for (int i = 0; i < texiC->getListDriver().size(); i++){
        Driver *d = texiC->getListDriver().front();
        texiC->getListDriver().pop_front();
        tcp->setClient(in->getConnOfDriver(d));
        tcp->sendData("go home");
        texiC->getListDriver().push_back(d);
    }
    in->finnish();
    delete texiC;
    delete g;
    delete m;
    sleep(1);
    tcp->~Tcp();
    return 0;
}
//a function that created threads to handle the drivers (clients)
void* createClientCon(void* in) {
    Information *info = (Information *) in;
    int *numOf = info->getNumOfDrivers();
    int conn;
    for(int i = 0; i< *numOf ;i++){
        conn = info->getTcp()->acceptt();
        if (conn < 0) {
            cout << "Connection not established!" << endl;
        } else {
            cout << "get connection with: " << conn <<endl;
            info->setConnection(conn);
            pthread_t myThread;
            int status = pthread_create(&myThread, NULL, managerClient, (void *) info);
            if (status) {
                cout << "ERROR! ";
            } else {
                pthread_join(myThread, NULL);
            }
        }
    }
}
//a function for manage (ger and insert) a new client
void* managerClient(void* in) {
    Information *info = (Information *) in;
    pthread_mutex_lock(info->lockClients());
    info->getTcp()->setClient(info->getConnection());
    pthread_mutex_unlock(info->lockClients());

    sleep(1);

    info->getTcp()->sendData("getting shimi");



    Driver dDummy;
    char buffer[1024];
    info->getTcp()->reciveData(buffer, sizeof(buffer));

    string str(buffer, sizeof(buffer));
    dDummy.setString(str);

    Driver *d = new Driver();
    d->setDriver(dDummy.load());

    pthread_mutex_lock(info->lockClients());
    info->addClient(d, info->getConnection());
    pthread_mutex_unlock(info->lockClients());

    sleep(1);
    info->getTcp()->sendData("thanks for sending shimi :)");
    str.clear();

    if (info->getTexiC()->getVehicle(d->getCabId())->isA()) {
        sleep(1);
        info->getTcp()->sendData("1");
        Cab *cab = boost::polymorphic_downcast<Cab *>
                (info->getTexiC()->getVehicle(d->getCabId()));
        cab->save();
        char bufferCar[1024];
        info->getTcp()->reciveData(bufferCar, sizeof(bufferCar));
        string str1(bufferCar);
        cout << "sending cab" << endl;//getting cab
        str1.clear();
        sleep(1);
        info->getTcp()->sendData(cab->serial_str);

        d->setTexi(cab);
        char buffer1[1024];

        info->getTcp()->reciveData(buffer1, sizeof(buffer1));

        string stMess(buffer1);

        cout << "Driver have cab" << endl;//we got the cab!

        stMess.clear();

    } else {
        sleep(1);
        info->getTcp()->sendData("0");
        LuxuryCab *cab =
                boost::polymorphic_downcast<LuxuryCab *>
                        (info->getTexiC()->getVehicle(d->getCabId()));

        cab->save();
        char bufferCar[1024];
        info->getTcp()->reciveData(bufferCar, sizeof(bufferCar));

        string str1(bufferCar);
        cout << str1 << endl;//getting cab
        sleep(1);
        info->getTcp()->sendData(cab->serial_str);

        char buffer1[1024];
        info->getTcp()->reciveData(buffer1, sizeof(buffer1));

        string stMess(buffer1);

        cout << stMess << endl;
    }
    pthread_mutex_lock(info->lockDriver());
    info->getTexiC()->setDrivers(d);
    pthread_mutex_unlock(info->lockDriver());

}
// a function for the thread of the trip info's, for calculate the path
void* calculateWay(void* inf) {
    Information *info = (Information *) inf;
    TripInfo* t = info->getTexiC()->getListTrips().back();
    Gps *gps = new Gps(t->getStartPoint(), t->getEndPoint());
    Map *m = info->getTexiC()->getMap();
    queue<CheckPoint *> way = gps->start(m->getGrid());
    t->convertToListInit(way);

}
/*
3 3
0
3
0,1,H,R
3
1,1,S,B
2
1,0,0,1,1,1,20,4
2
0,0,0,2,2,1,20,1
1
2
9
9
9
9
9
9
9
 */