
#ifndef EX3_PASSENGER_H
#define EX3_PASSENGER_H
#include <cstdlib>
#include "Person.h"
#include "CheckPoint.h"
//this class's purpose is to manage a passenger object.it inherits from the person class,
//and has a method for providing a number that represents the satisfaction from the trip.
class Passenger : public Person {
    //private member section
private:
    Point source;
    Point destination;
    //public member section
public:
    Passenger();
    Passenger(Point source, Point destinstion);
    virtual ~Passenger();
    int satisfactionFromTrip();
    Point getSource();
    Point getDestination();
    int getId();
    int getAge();
};



#endif //EX3_PASSENGER_