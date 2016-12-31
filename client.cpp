//
// Created by orian on 12/30/16.
//

#include <iostream>
#include <string>
#include <unistd.h>
#include "Udp.h"
#include "Cab.h"
#include "Driver.h"
#include "MaterialStatus.h"
using namespace std;
int main(int argc, char *argv[]) {
    Udp udpClient(0, atoi(argv[1]));
    udpClient.initialize();
    char dummy, status;
    MaterialStatus materialStatus;
    int id, age, exp, vehicleId;
    cin >> id >> dummy >> age  >> dummy >>status >> dummy >> exp >> dummy >>vehicleId;
    switch(status){
        case 'S' : {
            materialStatus = MaterialStatus :: SINGLE;
            break;
        }
        case 'M' : {
            materialStatus = MaterialStatus :: MARRIED;
            break;
        }
        case 'D' : {
            materialStatus = MaterialStatus :: DIVORCED;
            break;
        }
        case 'W' : {
            materialStatus = MaterialStatus :: WIDOWED;
            break;
        }
        default: {
            cout << "status not exist" << endl;
            break;
        }
    }
    Driver* driver = new Driver(id, age, exp, materialStatus, vehicleId);
    /*
    string idString;
    ostringstream convert;
    convert << id;
    idString = convert.str();
    udpClient.sendData(idString);
    */
}

/*
#include <iostream>
#include "TexiCenter.h"
#include <list>

using namespace std;

int main(){
    int idInput =0;
    int numOKInput=0;
    double tariff= 1;

    Cab* c = new Cab(idInput, numOKInput, tariff,CarColors::RED, CarsManufactor::FIAT);
    c->save();

    Cab c2 = c->load();
    cout<<"id: "<< c2.getID()<< endl;
    cout<<"tariff: "<< c2.getTariff()<<endl;
    if(c2.getColor() == CarColors::RED){
        cout <<"color: BLUE" <<endl;
    }
    delete c;

    int mP = 0;
    int nP = 0;
    int rID= 1;
    double t = 5.7;
    Point* sP = new Point(1,1);
    Point* eP = new Point(0,0);

    TripInfo *trip = new TripInfo(mP, nP, rID, t, sP, eP);

    trip->save();
    TripInfo trip2 = trip->load();

    cout<<"endPX: "<< trip2.getStartPoint()->getX_axis()<< endl;
    cout<<"endPY: "<< trip2.getStartPoint()->getY_axis()<< endl;
    cout<<"tariff: "<< trip2.getTarif()<<endl;
    Grid* g = new Grid(3,3);
    g->save();
    Grid g2 = g->load();
    cout << g2.getY();
    cout << g2.getX();
    Map* m = new Map(g);
    //list<Point> obs;
    //obs.push_back(Point(1,1));
    m->createO(Point(1,1));
    m->save();
    Map m2 = m->load();
    cout << m2.getListOfO().front().getX_axis() << "," <<m2.getListOfO().front().getY_axis();
    cout << m2.getGrid()->getX() <<"-" << m2.getGrid()->getY();
    delete trip;
}*/