
#ifndef EX3_VEHICLES_H
#define EX3_VEHICLES_H
#include "CarsManufactor.h"
#include "CarColors.h"
#include "TripInfo.h"
#include "CheckPoint.h"
#include <queue>

//this is an abstract class for a vehicle.
//it has a move method for the moving functionality/
class Vehicles {
    //public members section
public:
    virtual int move(int)=0;

    virtual int getID() = 0;

    virtual int getKM() = 0;

    virtual CarColors getColor() = 0;

    virtual CarsManufactor getCarType() = 0;

    virtual void setID(int) = 0;

    virtual void setKM(int) = 0;

    virtual double getTariff() = 0;

    virtual void setTariff(double) = 0;

    virtual void setADriver(bool) = 0;

    virtual bool hasADriver() = 0;
};
#endif //EX3_VEHICLES_H
