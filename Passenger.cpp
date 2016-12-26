
#include "Passenger.h"
//this is the default constructor for the passenger class
Passenger::Passenger() {
}
//this is the constructor for the passenger class
Passenger::Passenger(Point source, Point destination){
	this->source = source;
	this->destination = destination;
}
//this is the default destructor for the passenger class
Passenger::~Passenger() {
}
//this is a method for providing a number between 1 to 5, that represent satisfaction from trip.
int Passenger::satisfactionFromTrip() {
	int satisfaction = rand()% 5 + 1;
	return satisfaction;
}
//this is a getter method of the passenger's source
Point Passenger::getSource(){
	return this->source;
}
//this is a getter method of the passenger's destination
Point Passenger::getDestination(){
	return this->destination;
}
//this is a getter method of the passenger's id
int Passenger::getId(){
	return 0;
}
//this is a getter method of the passenger's age
int Passenger::getAge(){
	return 0;
}