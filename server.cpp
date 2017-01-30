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
#include <cstdlib>
#include "ThreadPool.h"
#include <iostream>
#include <string.h>
#include "pthread.h"
#include <boost/cast.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/serialization/list.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;
void* createClientCon(void*);
void* managerClient(void*);
void* calculateWay(void*);
map <int, int> options;
int main(int argc, char *argv[]) {
    Information *in;

    Tcp* tcp = new Tcp(1, atoi(argv[1]));
    tcp->initialize();
    int x,y, i, pOfAbs;
    Grid *g;
    Map *m;
    char damy;
    long time = 0;
    bool invalidInput;
    do {
        string input;
        cin.clear();
        getline(cin, input);
        invalidInput = false;
        size_t found = input.find_first_not_of(" ");
        string inputFixedSpaces = input.substr(found);
        size_t findMiddle = inputFixedSpaces.find(' ');
        if (findMiddle == -1) {
            cout << "-1" << endl;
            invalidInput = true;
            continue;
        }
        string xStr = inputFixedSpaces.substr(0, findMiddle).c_str();
        string yStr = inputFixedSpaces.substr(findMiddle + 1).c_str();
        x = atoi(xStr.c_str());
        y = atoi(yStr.c_str());
        if ( (x == 0 && xStr.at(0) != '0') ||(y == 0 && yStr.at(0) != '0')) {
            cout << "-1" << endl;
            invalidInput = true;
            continue;
        }
        if ( x <= 0 || y <= 0) {
            cout << "-1" << endl;
            invalidInput = true;
            continue;
        } else {
            g = new Grid(x, y);
            m = new Map(g);
            string inputObstacles;
            cin.clear();
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, inputObstacles);
            pOfAbs = atoi(inputObstacles.c_str());
            if (pOfAbs == 0 && inputObstacles.at(0) != '0') {
                cout << "-1" << endl;
                invalidInput = true;
                continue;
            }

            if (pOfAbs < 0) {
                cout << "-1" << endl;
                invalidInput = true;
                continue;
            } else {
                while (pOfAbs > 0) {
                    string inputObstacles;
                    cin.clear();
                    getline(cin, inputObstacles);
                    size_t findMiddle = inputObstacles.find(',');
                    if (findMiddle == -1) {
                        cout << "-1" << endl;
                        invalidInput = true;
                        break;
                    }
                    string xStr = inputObstacles.substr(0, findMiddle);
                    string yStr = inputObstacles.substr(findMiddle + 1);
                    x = atoi(xStr.c_str());
                    y = atoi(yStr.c_str());
                    if ( (x == 0 && xStr.at(0) != '0') ||(y == 0 && yStr.at(0) != '0')) {
                        cout << "-1" << endl;
                        invalidInput = true;
                        break;
                    }
                    if (x >= m->getGrid()->getX() || y >= m->getGrid()->getY() || x < 0 || y < 0){
                        cout << "-1" << endl;
                        invalidInput = true;
                        break;
                    }
                    m->createO(Point(x, y));
                    pOfAbs--;
                }

            }
        }
    } while (invalidInput);
    Grid *gDummy2;
    Driver dDummy;
    TripInfo *tIDummy;
    pthread_t tTrip;
    pthread_t t1;

    TexiCenter *texiC = new TexiCenter();

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
        cin.clear();
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
                break;
            }
            case 2: {
                int timeOfTrip;
                string input;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, input);
                size_t findMiddle = input.find(',');
                if (findMiddle == -1) {
                    cout << "-1" << endl;
                    break;
                }
                vector <string> vec;
                boost::split(vec,input,boost::is_any_of(","));
                if (vec.size() != 8) {
                    cout << "-1" << endl;
                    break;
                }
                id = atoi(vec[0].c_str());
                if (id < 0 || (vec[0].at(0) != '0' && id == 0) ) {
                    cout << "-1" << endl;
                    break;
                }
                startX = atoi(vec[1].c_str());
                if (startX < 0 || (vec[1].at(0) != '0' && startX == 0) ) {
                    cout << "-1" << endl;
                    break;
                }
                startY = atoi(vec[2].c_str());
                if (startY < 0 || (vec[2].at(0) != '0' && startY== 0) ) {
                    cout << "-1" << endl;
                    break;
                }
                if (startX >= texiC->getMap()->getGrid()->getX() ||
                        startY >= texiC->getMap()->getGrid()->getY()) {
                    cout << "-1" << endl;
                    break;
                }
                endX = atoi(vec[3].c_str());
                if (endX < 0 || (vec[3].at(0) != '0' && endX == 0) ) {
                    cout << "-1" << endl;
                    break;
                }
                endY = atoi(vec[4].c_str());
                if (endY < 0 || (vec[4].at(0) != '0' && endY== 0) ) {
                    cout << "-1" << endl;
                    break;
                }
                if (endX >= texiC->getMap()->getGrid()->getX() ||
                    endY >= texiC->getMap()->getGrid()->getY()) {
                    cout << "-1" << endl;
                    break;
                }
               timeOfTrip = atoi(vec[7].c_str());
                if (timeOfTrip <= 0 ) {
                    cout << "-1" << endl;
                    break;
                }

                tIDummy = new TripInfo(0, numOfPs, id, tariff,
                                       new Point(startX, startY), new Point(endX, endY), timeOfTrip);
                texiC->setTripI(tIDummy);
                int *num = new int(texiC->getListTrips().size());
                Information *inf = new Information(tcp, texiC, num);
                ThreadPool *pool = new ThreadPool(5);
                Task *task = new Task(calculateWay, inf);
                pool->addTask(task);
                break;
            }
            case 3: {
                string input;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, input);
                size_t findMiddle = input.find(',');
                if (findMiddle == -1) {
                    cout << "-1" << endl;
                    break;
                }
                vector <string> vec;
                boost::split(vec,input,boost::is_any_of(","));
                if (vec.size() != 4) {
                    cout << "-1" << endl;
                    break;
                }
                id = atoi(vec[0].c_str());
                if (id < 0 || (vec[0].at(0) != '0' && id == 0) ) {
                    cout << "-1" << endl;
                    break;
                }
                ch = vec[2].at(0);
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
                        cout << "-1" << endl;
                        continue;
                    }
                }
                ch2 = vec[3].at(0);
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
                        cout << "-1" << endl;
                        continue;
                    }
                }
                type = atoi(vec[1].c_str());
                if (type < 0) {
                    cout << "-1" << endl;
                    break;
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
                        cout << "-1" << endl;
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
                    cout << "-1" << endl;
                }
                break;
            }
            case 9: {
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
                                texiC->getListDriver().push_back(d);
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
            default:{
                if (i == 7) {
                    break;
                }
                cout << "-1" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    //in->finnish();
    //delete texiC;
    //delete g;
    //delete m;
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
    //might change to 2 (?) start + end might be there
    if (way.size() == 0) {
        info->getTexiC()->getListTrips().pop_back();
    } else {
        t->convertToListInit(way);
    }
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