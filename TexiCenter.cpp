
#include "TexiCenter.h"
//this is the constructor of the taxi center class

//this is the default constructor of the taxi center class
TexiCenter::TexiCenter(){

}
//this is the destructor of the taxi center class
TexiCenter::~TexiCenter() {
    //delete all the veicles
    for(int i = 0; i<this->vehicles.size(); i++){
        delete this->vehicles.front();
        this->vehicles.pop_front();
    }
    //delete all the drivers
    for(int i = 0; i<this->drivers.size(); i++){
        delete this->drivers.front();
        this->drivers.pop_front();
    }
    //delete all the trips
    for(int i = 0; i<this->tripsI.size(); i++){
        delete this->tripsI.front();
        this->tripsI.pop_front();
    }
}

//this is a method for adding a new driver to the taxi center
void TexiCenter::setDrivers(Driver* d){
    this->drivers.push_back(d);
}
//this is a method for adding a new list of driver to the taxi center
void TexiCenter::setListDrivers(list<Driver*> d){
    if(this->drivers.size()){this->drivers.clear();}
    this->drivers = d;
}
//this is a method for adding a new cab to the taxi center
void TexiCenter:: setVehicleCab(Vehicles* c){
    this->vehicles.push_back(c);
}
//this is a method for adding a new list of cab to the taxi center
void TexiCenter:: setListVehicles(list<Vehicles*> c){
    if(this->vehicles.size()){this->vehicles.clear();}
    this->vehicles = c;
}
//this is a method for adding a new trip info to the taxi center
void TexiCenter:: setTripI(TripInfo* t){
    this->tripsI.push_back(t);
}
//this is a method for adding a new trip info to the taxi center
void TexiCenter:: setListTripI(list<TripInfo*> t){
    if(this->tripsI.size()){this->tripsI.clear();}
    this->tripsI = t;
}

//this is a method for getting a call from a passenger
void TexiCenter:: getCall(Point, Point){}//need to build

//this is a method for sending a taxi to a passenger
void TexiCenter:: sendTexi(Driver* d, TripInfo* t, queue <CheckPoint*> q){}


//this is a method for getting the cabs
Vehicles* TexiCenter::getVehicle(int iDC){
    for(int i = 0; i<this->vehicles.size(); i++){
        Vehicles* v = this->vehicles.front();
        this->vehicles.pop_front();
        if(v->getID() == iDC){
            this->vehicles.push_back(v);
            return v;
        }else{this->vehicles.push_back(v);}
    }
}

//this is a method for getting the trip infos
TripInfo* TexiCenter:: getTripI(int iDT){
    for(int i = 0; i < this->tripsI.size(); i++){
        TripInfo* t = this->tripsI.front();
        this->tripsI.pop_front();
        if(t->getIdRide() == iDT){
            this->tripsI.push_back(t);
            return t;
        }
        else{this->tripsI.push_back(t);}
    }
}

//this is a method for getting a specific location
Point TexiCenter::getLocation(Driver* d){
    return d->getLocation();
}
//this method returns a driver according to his id number
Driver* TexiCenter::getDriver(int iDD){
    //list<Driver*>
    for(int i = 0; i < this->drivers.size(); i++){
        Driver* d = this->drivers.front();
        this->drivers.pop_front();
        if(d->getId() == iDD){
            this->drivers.push_back(d);
            return d;
        }
        else{
            this->drivers.push_back(d);
        }
    }
}
//this method enables acess to the list of the drivers in the texi center
list<Driver*> TexiCenter::getListDriver(){
    return this->drivers;
}
//this method enables acess to the list of the veicles in the texi center
list<Vehicles*> TexiCenter::getListVehicles(){
    return this->vehicles;
}
//this method enables acess to the list of the trips in the texi center
list<TripInfo*> TexiCenter::getListTrips(){
    return this->tripsI;
}