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
//this is a default constructor of the driver class
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
void Driver::drive(queue<CheckPoint *> q) {

    this->getTripInfo()->setMetters(this->getTexiOfDriver()->move(q.size()));
    this->setLocation(*this->getTripInfo()->getEndPoint());
}
//this is a boolean method for car's exsistance
bool Driver::getExist(){
    return this->existCar;
}
int Driver::getCabId() {
    return this->cabId;
}