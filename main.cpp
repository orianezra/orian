

#include <string.h>
#include <iostream>
#include "Grid.h"
#include "Map.h"
#include "TexiCenter.h"
using namespace std;
int main(){

    int i,j, pOfAbs;
    char damy;

    cin >> i >> j;
    Grid* gDummy2;
    Grid* g = new Grid(i, j);
    Map* m = new Map(g);
    TexiCenter* texiC = new TexiCenter();

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
                cin >> id >> damy >> age  >> damy >>status >> damy >> exp >> damy >>vId;
                switch(status){
                    case 'S' : {
                        mS = MaterialStatus :: SINGLE;
                        break;
                    }
                    case 'M' : {
                        mS = MaterialStatus :: MARRIED;
                        break;
                    }
                    case 'D' : {
                        mS = MaterialStatus :: DIVORCED;
                        break;
                    }
                    case 'W' : {
                        mS = MaterialStatus :: WIDOWED;
                        break;
                    }
                    default: {
                        cout << "status not exist" << endl;
                        break;
                    }
                }
                Driver* dDummy = new Driver(id, age, exp, mS, vId);
                dDummy->setMap(m);
                texiC->setDrivers(dDummy);
                break;
            }
            case 2:{
                cin >> id >> damy >> startX >> damy >> startY >> damy
                    >> endX >> damy >> endY >> damy >> numOfPs >> damy >>tariff;
                TripInfo* tIDummy = new TripInfo(0, numOfPs, id, tariff,
                                                 new Point(startX, startY), new Point(endX, endY));
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
            case 6:{
                if(!texiC->getListVehicles().empty() && !texiC->getListDriver().empty()){
                    list<Driver*> drivers = texiC->getListDriver();
                    list<Vehicles*> listV = texiC->getListVehicles();
                    int ls = texiC->getListDriver().size();
                    for(int g = 0; g < ls; g++){
                        Driver* dDummy = drivers.front();
                        drivers.pop_front();
                        if(!dDummy->getExist()){
                            for(int v =0; v<listV.size(); v++){
                                Vehicles* vCab = listV.front();
                                listV.pop_front();
                                if ((!vCab->hasADriver())){
                                    dDummy->setTexi(vCab);
                                    listV.push_back(vCab);
                                    drivers.push_back(dDummy);
                                    break;
                                } else{
                                    listV.push_back(vCab);}
                            }
                        }else{
                            drivers.push_back(dDummy);
                        }
                    }
                    texiC->setListDrivers(drivers);
                    texiC->setListVehicles(listV);
                }
                else{break;}
                for(int n = 0; n < texiC->getListDriver().size(); n++) {
                    int size = texiC->getListTrips().size();
                    if(size){
                        Gps* gps = new Gps(texiC->getListTrips().front()->getStartPoint()
                                ,texiC->getListTrips().front()->getEndPoint());
                        list<Driver*> lDDummy = texiC->getListDriver();

                        gDummy2 = lDDummy.front()->getMap()->getGrid();
                        queue <CheckPoint*> Q = gps->start(gDummy2);
                        list<TripInfo*> tL = texiC->getListTrips();
                        TripInfo* t = tL.front();
                        tL.pop_front();
                        lDDummy.front()->setTripInfo(t);
                        Driver* driverDumm = lDDummy.front();
                        lDDummy.pop_front();
                        driverDumm->drive(Q);
                        lDDummy.push_back(driverDumm);
                        texiC->setListDrivers(lDDummy);
                        texiC->setListTripI(tL);
                        delete gps;
                        delete gDummy2;
                    }
                }
                break;
            }
        }
    }
    while(i != 7);
    delete texiC;
    delete g;
    delete m;
    exit(0);
}