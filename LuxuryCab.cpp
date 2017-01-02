
#include "LuxuryCab.h"

//this is the constructor of the LuxuryCab class
LuxuryCab::LuxuryCab(int idInput, int kmInput, double tariff, CarColors c, CarsManufactor m) {
    this->id = idInput;
    this->numOfKM = kmInput;
    this->tariff = tariff;
    this->color = c;
    this->type = m;
    this->hasDriver = false;
    this->moveByTwo = 2;
}
//this is the destructor of the LuxuryCab class
LuxuryCab::~LuxuryCab() {
}
//this is the destructor of the LuxuryCab class
LuxuryCab::LuxuryCab() {
}
//this is a move method for the LuxuryCab
int LuxuryCab :: move() {
    return this->numOfKM+=this->moveByTwo;
}
//this is a getter method for the color of the luxurycab
CarColors LuxuryCab::getColor() {
    return this->color;
}
//this is a getter method for the manufactor of the luxurycab
CarsManufactor LuxuryCab::getCarType() {
    return this->type;
}
//this is a getter method for the id of the LuxuryCab
int LuxuryCab::getID() {
    return this->id;
}
//this is a setter method for the id of the LuxuryCab
void LuxuryCab::setID(int id) {
    this->id = id;
}

//this is a getter method for the number of km that the car has passed
int LuxuryCab::getKM() {
    return this->numOfKM;
}
//this is a setter method for the number of km that the car has passed
void LuxuryCab::setKM(int nOK) {
    this->numOfKM += nOK;
}

//this is a getter method for the tarrif
double LuxuryCab::getTariff() {
    return this->tariff;
}
//this is a setter method for the tarrif
void LuxuryCab::setTariff(double tariff) {
    this->tariff = tariff;
}
//this method checks if one trip info is different than tthe other
bool  LuxuryCab::operator !=(const LuxuryCab &other) const{
    if (this->id != other.id) {
        return true;
    }else {
        return false;
    }
}
//getter method for the has driver member
bool LuxuryCab::hasADriver(){
    return this->hasDriver;
}
//setter for the has driver member
void LuxuryCab::setADriver(bool b){
    this->hasDriver = b;
}
//setter for the luxury cab itself, after passing serialization
void LuxuryCab::setLuxuryCab(LuxuryCab c) {
    this->id = c.id;
    this->numOfKM = c.numOfKM;
    this->tariff = c.tariff;
    this->color = c.color;
    this->type = c.type;
    this->hasDriver = c.hasDriver;
    this->moveByTwo = c.moveByTwo;
}
//setter for the serial string member
void LuxuryCab::setString(string s) {
    this->serial_str = s;
}
//check for the type of the car.
bool LuxuryCab::isA() {
    return false;
}
//get the car's movement
int LuxuryCab::getTheMove() {
    return this->moveByTwo;
}