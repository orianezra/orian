
#ifndef EX3_TRIPINFO_H
#define EX3_TRIPINFO_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <fstream>

#include "Point.h"
//this class's purpose is to manage trip info object
//it holds information about a trip
class TripInfo {
    //private member section
private:
    int rideId;
    int mettersPass;
    Point* startP;
    Point* endP;
    double tarif;
    int numOfPassengers;
    //public member section
public:
    TripInfo(int mP, int nP, int rID, double t, Point* sP, Point* eP);
    TripInfo();
    ~TripInfo();
    void setIdRide(int);
    void setMetters(int);
    void setNumOfPassangers(int);
    void setTarif(double);
    void setEndPoint(Point*);
    void setStartPoint(Point*);
    int getIdRide();
    int getMetters();
    int getNumOfPassangers();
    double getTarif();
    Point* getEndPoint();
    Point* getStartPoint();
    bool operator !=(const TripInfo &other) const;
};

#endif //EX3_TRIPINFO