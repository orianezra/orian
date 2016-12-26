//

#ifndef EX3_TEXICENTER_H
#define EX3_TEXICENTER_H

#include <iostream>
#include <list>
#include <string>
#include "Driver.h"
#include "TripInfo.h"
#include "CheckPoint.h"
//#include "Vehicles.h"
using namespace std;
//this class's purpose is to manage a texi center object
//it holds the information about the drivers' cabs and trip infos.
class TexiCenter {
    //private member section
private:
    list<Driver*> drivers;
    list<Vehicles*> vehicles;
    list<TripInfo*> tripsI;
    CheckPoint location;
//public member section
protected:

public:
    TexiCenter();
    //TexiCenter(list<Driver*> ,list<Cab*> ,list<TripInfo*>);
    ~TexiCenter();
    void setDrivers(Driver* d);
    void setListDrivers(list<Driver*>);
    void setVehicleCab(Vehicles*);
    void setListVehicles(list<Vehicles*>);
    void setTripI(TripInfo*);
    void setListTripI(list<TripInfo*>);
    void sendTexi(Driver* , TripInfo* , queue <CheckPoint*> );
    void getCall(Point, Point);//this func ask the gps about the faster way and ask for sendtexi
    list<Driver*> getListDriver();
    list<Vehicles*> getListVehicles();
    list<TripInfo*> getListTrips();
    Driver* getDriver(int);
    Vehicles* getVehicle(int);
    TripInfo* getTripI(int);//maybe by id of the rode
    Point getLocation(Driver*);//return by spes driver! so need to check the driver that we pull
};

#endif //EX3_TEXICENTER_H
