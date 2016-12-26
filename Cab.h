
#ifndef EX3_CAB_H
#define EX3_CAB_H

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <iostream>
#include <fstream>

#include "CarsManufactor.h"
#include "CarColors.h"
#include "Vehicles.h"
#include "CheckPoint.h"
#include <queue>
#include "TripInfo.h"
using namespace std;

//this is a class to manage a car object
//it has an id, holds and updates number of kms, and has a method for moving functionality.
class Cab : public Vehicles{
    //private members section

private:

    int id;
    int numOfKM;
    enum CarsManufactor type;
    enum CarColors color;
    double tarif;
    bool hasDriver;
    //public members section
public:
    Cab();
    Cab(int, int, double, CarColors, CarsManufactor);
    ~Cab();
    int move(int);
    int getID();
    int getKM();
    double getTariff();
    CarColors getColor();
    CarsManufactor getCarType();
    void setID(int id);
    void setKM(int km);
    void setTariff(double tarif);
    bool hasADriver();
    void setADriver(bool b);
    void save();
    void load();
    bool operator !=(const Cab &other) const;
};


namespace boost {
    namespace serialization {
        template<class Archive>
        void serialize(Archive &ar, Cab & c, const unsigned int version) {
            ar & c.getID();
            ar & c.getColor();
            ar & c.getCarType();
            ar & c.getKM();
            ar & c.getTariff();
            ar & c.hasADriver();
        }
    }
}
#endif //EX3_CAB_H
