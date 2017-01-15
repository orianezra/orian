#include "Tcp.h"
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "Grid.h"
#include "Map.h"
#include "TexiCenter.h"
#include "Information.h"
#include "pthread.h"
#include <boost/cast.hpp>
#include <map>
#include <boost/serialization/list.hpp>
using namespace std;
using namespace boost;
void* createClientCon(void*);
void* managerClient(void*);
void* calculateWay(void*);
map <Driver*, int> options;
int main(int argc, char *argv[]) {
    Information *in;
    Tcp *tcp = new Tcp(1, atoi(argv[1]));
    //tcp->initialize();
    int i, j, pOfAbs;
    char damy;
    long time;
    cin >> i >> j;
    Grid *gDummy2;
    Driver dDummy;
    TripInfo *tIDummy;
    pthread_t tTrip;
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
                pthread_t t1;
                int *num = new int(numOfDrivers);
                tcp->initialize();
                in = new Information(tcp, texiC, num);
                int status = pthread_create(&t1, NULL, createClientCon, (void *) in);
                pthread_join(t1, NULL);
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
                Driver *d = texiC->getListDriver().front();
                TripInfo *t;
                //loop over the trips, check if its the time
                for (int i = 0; i < texiC->getListTrips().size(); i++) {
                    t = texiC->getListTrips().front();
                    texiC->getListTrips().pop_front();
                    if (time == t->getTimeOfTrip()) {

                        d->setTripInfo(t);
                        t->getWay().pop_front();
                        texiC->upData(d);
                        int firstOpt = 1;
                        options.insert(std::pair<Driver *, int>(d, firstOpt));

                    } else {
                        texiC->getListTrips().push_back(t);
                    }
                    if (time < t->getTimeOfTrip()) {
                        int secondOpt = 2;
                        options.insert(std::pair<Driver *, int>(d, secondOpt));

                    } else if (d->ifHasTrip()) {
                        int thirdOpt = 3;
                        options.insert(std::pair<Driver *, int>(d, thirdOpt));
                    }
                }
                time++;
                break;
            }
        }
    } while (i != 7);
    tcp->sendData("go home");
    delete texiC;
    delete g;
    delete m;
    sleep(1);
    tcp->~Tcp();
    return 0;
}

void* createClientCon(void* in) {
    Information *info = (Information *) in;
    int *numOf = info->getNumOfDrivers();
    int conn;
    while (*numOf) {
        conn = info->getTcp()->acceptt();
        if (conn < 0) {
            cout << "Connection not established!" << endl;

        } else {
            pthread_t myThread;

            int status = pthread_create(&myThread, NULL, managerClient, (void *) info);
            if (status) {
                cout << "ERROR! ";
            }
            pthread_join(myThread, NULL);
            info->setConnection(&conn);
        }
        ///////////////added
        (*numOf)--;

    }
}
    void* managerClient(void* in) {
        Information *info = (Information *) in;

        sleep(1);
        info->getTcp()->sendData("getting shimi");

        Driver dDummy;
        char buffer[1024];
        info->getTcp()->reciveData(buffer, sizeof(buffer));
        string str(buffer, sizeof(buffer));
        dDummy.setString(str);
        Driver *d = new Driver();
        d->setDriver(dDummy.load());
        info->getTexiC()->setDrivers(d);
        info->addClient(d, info->getConnection());
        sleep(1);
        info->getTcp()->sendData("thanks for sending shimi :)");

        if (info->getTexiC()->getVehicle(d->getCabId())->isA()) {
            sleep(1);
            info->getTcp()->sendData("1");
            Cab *cab = boost::polymorphic_downcast<Cab *>
                    (info->getTexiC()->getVehicle(d->getCabId()));
            cab->save();
            char bufferCar[1024];
            info->getTcp()->reciveData(bufferCar, sizeof(bufferCar));
            string str1(bufferCar);
            cout << str1 << endl;//getting cab

            sleep(1);
            info->getTcp()->sendData(cab->serial_str);
            info->getTexiC()->getListDriver().front()->setTexi(cab);
            char buffer1[1024];
            info->getTcp()->reciveData(buffer1, sizeof(buffer1));
            string stMess(buffer1);
            cout << stMess << endl;//we got the cab!

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
            info->getTexiC()->getListDriver().front()->setTexi(cab);
            char buffer1[1024];
            info->getTcp()->reciveData(buffer1, sizeof(buffer1));
            string stMess(buffer1);
            cout << stMess << endl;

        }
        int option = options.find(d)->second;
        switch (option) {
            case 1: {
                sleep(1);
                info->getTcp()->sendData("start triping shimi");
                d->getTripInfo()->save();
                sleep(1);
                info->getTcp()->sendData(d->getTripInfo()->serial_str);

            }
            case 2: {
                sleep(1);
                info->getTcp()->sendData("you can`t drive :(");
            }
            case 3: {
                sleep(1);
                info->getTcp()->sendData("you can drive :)");
                char buffer0[2000];
                info->getTcp()->reciveData(buffer0, sizeof(buffer0));
                string stMessage(buffer0);
                if (stMessage.compare("drive one step") == 0) {
                    info->getTexiC()->upData(info->getTexiC()->getListDriver().front());
                    if (info->getTexiC()->getListDriver().front()->getTripInfo()->getWay().size() == 0) {
                        sleep(1);
                        info->getTcp()->sendData("end of trip");
                        info->getTexiC()->getListTrips().pop_front();
                        d->setHasTrip(false);
                    }
                }
            }
        }
    }
void* calculateWay(void* inf) {
    Information *info = (Information *) inf;
    info->lockTrips();
    TripInfo* t = info->getTexiC()->getListTrips().back();
    info->unLockTrips();
    Gps *gps = new Gps(t->getStartPoint(), t->getEndPoint());
    Map *m = info->getTexiC()->getMap();
    queue<CheckPoint *> way = gps->start(m->getGrid());
    t->convertToListInit(way);

}