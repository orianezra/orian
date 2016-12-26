#include "TripInfo.h"
//this is the constructor of the trip info class
TripInfo::TripInfo(int mP, int nP, int rID, double t, Point* sP, Point* eP) {
    this->mettersPass = mP;
    this->numOfPassengers = nP;
    this->rideId = rID;
    this->tarif = t;
    this->endP = eP;
    this->startP = sP;
}
//this is the destructor of the trip info class
TripInfo::~TripInfo() {
    delete this->endP;
    delete this->startP;
}
//default constructor
TripInfo::TripInfo() {
}

//this is a method for setting the ride id
void TripInfo::setIdRide(int iD){
    this->rideId = iD;
}
//this is a method for setting the number of meters passed
void TripInfo::setMetters(int m){
    this->mettersPass += m;
}
//this is a method for setting the number of passengers in a trip
void TripInfo::setNumOfPassangers(int nOP){
    this->numOfPassengers += nOP;
}
//this is a method for setting the tarrif
void TripInfo::setTarif(double t){
    this->tarif = t;
}
//this is a method for setting the end point of the trip
void TripInfo::setEndPoint(Point* e){
    this->endP = e;
}
//this is a method for setting the start point of the trip
void TripInfo::setStartPoint(Point* s){
    this->startP = s;
}
//this is a method for getting the id of the trip
int TripInfo::getIdRide(){
    return this->rideId;
}

//this is a method for getting the number of meters passed
int TripInfo::getMetters(){
    return this->mettersPass;
}

//this is a method for getting the number of passengers
int TripInfo::getNumOfPassangers(){
    return this->numOfPassengers;
}

//this is a method for getting the tariff
double TripInfo::getTarif(){
    return this->tarif;
}

//this is a method for getting the end point
Point* TripInfo::getEndPoint(){
    return this->endP;
}

//this is a method for getting the start point
Point* TripInfo::getStartPoint(){
    return this->startP;
}
//this method compere id rode and return true if not same.
bool TripInfo::operator !=(const TripInfo &other) const{
    if(other.rideId != this->rideId){
        return true;
    }
    return false;
}