#include "Cab.h"
using namespace boost::archive;

//this is the constructor of the cab class
Cab::Cab(int idInput, int numOKInput, double tariff, CarColors c, CarsManufactor m) {
    this->id = idInput;
    this->numOfKM = numOKInput;
    this->tariff = tariff;
    this->color = c;
    this->type = m;
    this->hasDriver = false;
    this->moveByOne = 1;
}
//this is the default constructor of the cab's class
Cab::Cab(){}
//this is the destructor of the cab class
Cab::~Cab() {
}
void Cab::setCab(Cab c) {
    this->id = c.id;
    this->numOfKM = c.numOfKM;
    this->tariff = c.tariff;
    this->color = c.color;
    this->type = c.type;
    this->hasDriver = c.hasDriver;
    this->moveByOne = c.moveByOne;
}
//this is a move method for the cab
int Cab::move() {
    return this->numOfKM += this->getTheMove();

}
int Cab::getTheMove() {
    return this->moveByOne;
}
//this is a getter method for the id of the cab
int Cab::getID() {
    return this->id;
}
//this is a getter method for the number of km that the car has passed
int Cab::getKM() {
    return this->numOfKM;
}
//this is a getter method for the tarrif
double Cab::getTariff() {
    return this->tariff;
}
//this is a getter method for the color of the cab
CarColors Cab::getColor() {
    return this->color;
}
//this is a getter method for the manufactor of the cab
CarsManufactor Cab::getCarType() {
    return this->type;
}
//this is a setter method for the cab's id
void Cab::setID(int id) {
    this->id = id;
}
//this is a setter method for the cab's number of kilometers
void Cab::setKM(int km) {
    this->numOfKM += km;
}
//this is a setter method for the cab's tarrif
void Cab::setTariff(double tarif) {
    this->tariff = tarif;
}
//this method checks if one trip info is different than tthe other
bool  Cab::operator !=(const Cab &other) const{
    if (this->id != other.id) {
        return true;
    }else {
        return false;
    }
}
//this is a getter method for a driver's exsistance of the car
bool Cab::hasADriver(){
    return this->hasDriver;
}
//setter for the hs driver member
void Cab::setADriver(bool b){
    this->hasDriver = b;
}
//this is a setter method for the serialized string
void Cab::setString(string s) {
    this->serial_str = s;
}
//this method determines the cab's type. if this is a standart cab, return true
bool Cab::isA() {
    return true;
}