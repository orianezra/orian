
#include "Udp.h"
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "Grid.h"
#include "Map.h"
#include "TexiCenter.h"
#include <boost/cast.hpp>
#include <boost/serialization/list.hpp>
using namespace std;
using namespace boost;
int main(int argc, char *argv[]) {

    Udp udp(1, atoi(argv[1]));
    udp.initialize();
    int i,j, pOfAbs;
    char damy;
    long time = 0;
    cin >> i >> j;
    Grid* gDummy2;
    Driver dDummy;
    Grid* g = new Grid(i, j);
    Map* m = new Map(g);
    TexiCenter* texiC = new TexiCenter();
    bool hasTrip = false;
    cin >> pOfAbs;
    if(pOfAbs >0){
        int arr[2];
        while(pOfAbs > 0) {
            cin >> arr[0] >> damy >> arr[1];
            m->createO(Point(arr[0], arr[1]));
            pOfAbs--;

        }
    }

    do{
        int id, age, exp, vId, startX, startY, endX, endY, numOfPs, type;
        double tariff;
        char ch;
        char status;
        char ch2;

        MaterialStatus mS;
        CarColors color;

        CarsManufactor cMF;
        cin >> i;
        switch(i){
            case 1:{
                int numOfDrivers;
                cin >> numOfDrivers;


                char buffer[1024];
                udp.reciveData(buffer, sizeof(buffer));
                string str(buffer, sizeof(buffer));
                dDummy.setString(str);
                Driver* d = new Driver();
                d->setDriver(dDummy.load());
                texiC->setDrivers(d);
                //udp.sendData("thanks for sending shimi :)");

                if(texiC->getVehicle(d->getCabId())->isA()){
                    udp.sendData("1");
                    Cab* cab = boost::polymorphic_downcast<Cab*>(texiC->getVehicle(d->getCabId()));
                    cab->save();
                    udp.sendData(cab->serial_str);
                    texiC->getListDriver().front()->setTexi(cab);
                    //char buffer1[1024];
                    //udp.reciveData(buffer1, sizeof(buffer1));
                    //string stMess(buffer1);
                    //cout << stMess <<endl;//we got the cab!

                }else{
                    udp.sendData("0");
                    LuxuryCab* cab = boost::polymorphic_downcast<LuxuryCab*>(texiC->getVehicle(d->getCabId()));
                    cab->save();
                    udp.sendData(cab->serial_str);
                    texiC->getListDriver().front()->setTexi(cab);
                    //char buffer1[1024];
                    //udp.reciveData(buffer1, sizeof(buffer1));
                    //string stMess(buffer1);
                    //cout << stMess <<endl;
                }
                break;
            }
            case 2:{
                unsigned long timeOfTrip;
                cin >> id >> damy >> startX >> damy >> startY >> damy
                    >> endX >> damy >> endY >> damy >> numOfPs >> damy >>tariff >> damy >> timeOfTrip;
                TripInfo* tIDummy = new TripInfo(0, numOfPs, id, tariff,
                                                 new Point(startX, startY), new Point(endX, endY), timeOfTrip);
                texiC->setTripI(tIDummy);
                break;
            }
            case 3:{
                cin >> id >> damy >>  type >> damy >> ch >> damy >> ch2;
                switch (ch){
                    case 'H':{
                        cMF = CarsManufactor::HONDA;
                        break;
                    }
                    case 'F':{
                        cMF = CarsManufactor::FIAT;
                        break;
                    }
                    case 'S':{
                        cMF = CarsManufactor::SUBARO;
                        break;
                    }
                    case 'T':{
                        cMF = CarsManufactor::TESLA;
                        break;
                    }
                    default: {
                        cout << "type not exist" << endl;
                        break;
                    }
                }
                switch (ch2){
                    case 'B':{
                        color = CarColors::BLUE;
                        break;
                    }
                    case 'R':{
                        color = CarColors::RED;
                        break;
                    }
                    case 'G':{
                        color = CarColors::GREEN;
                        break;
                    }
                    case 'W':{
                        color = CarColors::WHITE;
                        break;
                    }
                    case 'P':{
                        color = CarColors::PINK;
                        break;
                    }
                    default: {
                        cout << "color not exist" << endl;
                        break;
                    }
                }
                switch (type){
                    case 1:{
                        Cab* cabDummy = new Cab(id, 0, 0, color, cMF);
                        texiC->setVehicleCab(cabDummy);
                        break;
                    }
                    case 2:{
                        LuxuryCab* cabDummy = new LuxuryCab(id, 0, 0, color, cMF);
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
            case 4:{
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
            case 6:{}
            case 9: {

                TripInfo* t;
                if(time == texiC->getListTrips().front()->getTimeOfTrip()){
                    //check the place of shimi!!
                    udp.sendData("start triping shimi");
                    t = texiC->getListTrips().front();

                    Gps* gps = new Gps(t->getStartPoint(), t->getEndPoint());
                    queue<CheckPoint*> way = gps->start(m->getGrid());
                    t->convertToListInit(way);
                    t->save();

                    //the tzivot
                    udp.sendData(t->serial_str);
                    texiC->getListDriver().front()->setTripInfo(t);
                    t->getWay().pop_front();
                    texiC->upData(texiC->getListDriver().front());
                    hasTrip = true;

                }
                else if(time < texiC->getListTrips().front()->getTimeOfTrip()) {
                    udp.sendData("you can`t drive :(");
                    //time++;
                    //break;
                }
                else if (hasTrip){
                    udp.sendData("you can drive :)");
                    char buffer0[2000];
                    udp.reciveData(buffer0, sizeof(buffer0));
                    string stMessage(buffer0);
                    if(stMessage.compare("drive one step")==0){
                        texiC->upData(texiC->getListDriver().front());
                    } else if ( stMessage.compare("finnish the drive") == 0){
                        texiC->getListTrips().pop_front();
                        hasTrip = false;
                    }
                    }

                time++;
                break;
            }
        }
    }
    while(i != 7);
    delete texiC;
    delete g;
    delete m;
    return 0;
}
/*
3 3
0
3
0,1,H,R
2
0,0,0,2,2,1,20,1
1
 */