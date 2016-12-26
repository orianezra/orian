
#ifndef EX3_DRIVER_H
#define EX3_DRIVER_H

#include "Person.h"
#include "Cab.h"
//#include "Vehicles.h"
#include "LuxuryCab.h"
#include "Gps.h"
#include "MaterialStatus.h"
#include "Map.h"
//this class's purpose is to manage a driver object.
//it inherits from person, and has the functionality of having a car.
class Driver : public Person {
    //private members section
private:
    int id;
    int age;
    MaterialStatus status;
    int yearsOfEp;
    int avgSatisfaction;
    Vehicles* texiInfo;
    Gps* waze;
    Point location;
    Map* map;
    bool existCar;
    TripInfo* trip;
    //public members section
public:
    void setLocation(Point);
    Point getLocation();

    Driver(int, int, int, MaterialStatus, int);
    Driver();
    virtual ~Driver();
    void setTripInfo(TripInfo*);
    TripInfo* getTripInfo();
    void setTexi(Vehicles* c);
    Vehicles* getTexiOfDriver();
    void setMap(Map*);
    Map* getMap();
    void drive(queue <CheckPoint*>);
    int getAge();
    int getId();
    void setGps(Gps* g);
    Gps* getGps();
    bool getExist();
    int getSatisfaction();
    MaterialStatus getStatus();
    int getYearsOfExperiance();
    void setStatus(MaterialStatus status);

    void setSatisfaction(int st);
    bool operator !=(const Driver &other) const;
};

#endif //EX3_DRIVER_H