//#include <boost/archive/xml_oarchive.hpp>
//#include <boost/archive/xml_iarchive.hpp>
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
}
//this is the default constructor of the cab's class
Cab::Cab(){}
//this is the destructor of the cab class
Cab::~Cab() {
}
//this is a move method for the cab
int Cab::move(int sizeToMove) {
    return this->numOfKM += sizeToMove;

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

/*
void Cab::save()
{
    std::ofstream file("archive.xml");
    boost::archive::xml_oarchive oa(file);

    oa & BOOST_SERIALIZATION_NVP(*this);
}*/
//BOOST_CLASS_EXPORT(Vehicles)
bool Cab::isStandart() {
    return true;
}