#include "Driver.h"

//this is the constructor of the driver class
Driver::Driver(int id, int age , int i, MaterialStatus status, int cabId) {
    this->id = id;
    this->age = age;
    this->cabId = cabId;
    this->yearsOfEp = i;
    this->status = status;
    this->location = Point(0,0);
    this->existCar = false;
}
void Driver::setDriver(Driver d) {
    this->id = d.id;
    this->age = d.age;
    this->cabId = d.cabId;
    this->yearsOfEp = d.yearsOfEp;
    this->status = d.status;
    this->location = d.location;
    this->existCar = d.existCar;
}
//constructor of the driver class
Driver::Driver(){}
//this is the destructor of the driver class
Driver::~Driver() {
    delete this->trip;
}
//this is the setter method for setting a texi to a given driver
void Driver:: setTexi(Vehicles* texi) {
    this->texiInfo = texi;
    this->texiInfo->setADriver(true);
    this->existCar = true;
}
//this is a method for getting the driver's age
int Driver::getAge() {
    return this->age;
}
//this is a getter method for the driver's id
int Driver::getId() {
    return this->id;
}
//this is a setter method for the driver's GPS
void Driver::setGps(Gps* g) {
    this->waze = g;
}
//this is a getter method for the driver's GPS
Gps* Driver::getGps(){
    return this->waze;
}
//this is a getter method for the driver's status
MaterialStatus Driver::getStatus() {
    return this->status;
}
//this is a getter method for the driver's years of experience
int Driver::getYearsOfExperiance(){
    return this->yearsOfEp;
}
//this is a setter method for the driver's status
void Driver::setStatus(MaterialStatus status) {
    this->status = status;
}
//this is a getter method for the driver's cab
Vehicles* Driver::getTexiOfDriver(){
    return this->texiInfo;
}
//this is a method for overloading the opertor !=
bool  Driver::operator !=(const Driver &other) const{
    if (this->id == other.id) {
        return false;
    } else {
        return true;
    }
}
//this is a getter method for the satisfaction from the driver
int Driver::getSatisfaction() {
    return this->avgSatisfaction;
}
//this is a method for setting the satisfaction of the driver
void Driver::setSatisfaction(int st) {
    this->avgSatisfaction = st;
}
//this is a method for setting the driver's current location
void Driver::setLocation(Point point) {
    this->location = point;
}
//this is a getter method for the driver's current location
Point Driver::getLocation() {
    return this->location;
}
//this is a setter method for the driver's map
void Driver::setMap(Map* m) {
    this->map = m;
}
//this is a getter method for the driver's map
Map* Driver::getMap() {
    return this->map;
}
//this is a setter method for the driver's trip info
void  Driver::setTripInfo(TripInfo* trip){
    this->trip = trip;
}
//this is a getter method for the driver's trip info
TripInfo*  Driver::getTripInfo(){
    return this->trip;
}
//this method enabeles the driver to drive (get to the end point of the trip)
void Driver::drive(list<CheckPoint *> q) {
    //might not get the list, take it from shimi's trip info :) 
    this->getTripInfo()->setMetters(this->getTexiOfDriver()->move(q.size()));
    this->setLocation(*this->getTripInfo()->getEndPoint());
}
//this is a boolean method for car's exsistance
bool Driver::getExist(){
    return this->existCar;
}
//this is a getter methos for the cab's id
int Driver::getCabId() {
    return this->cabId;
}
//this is a distance calcularing method
unsigned long Driver::disCalculation(Point other){
    this->waze->setStart(&this->location);
    this->waze->setEnd(&other);
    queue <CheckPoint*> q = this->waze->start(this->map->getGrid());
    return q.size();
}
//this is a setter method for the string
void Driver::setString(string s) {
    this->serial_str = s;
}