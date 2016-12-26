
#ifndef EX3_LUXURYCAB_H
#define EX3_LUXURYCAB_H
#include "CarsManufactor.h"
#include "CarColors.h"
#include "Vehicles.h"
#include "TripInfo.h"
#include "CheckPoint.h"
#include <queue>

//this is a class to manage a car object
//it has an id, holds and updates number of kms, and has a method for moving functionality.
class LuxuryCab : public Vehicles {
    //private members section
private:
    int id;
    int numOfKM;
    enum CarsManufactor type;
    enum CarColors color;
    double tariff;
    bool hasDriver;
    //public members section
public:
    LuxuryCab();
    LuxuryCab(int, int, double, CarColors, CarsManufactor);
    ~LuxuryCab();
    int move(int);

    int getID();
    int getKM();
    double getTariff();
    bool hasADriver();
    void setADriver(bool b);
    void setID(int id);
    void setKM(int km);
    void setTariff(double tarif);

    CarColors getColor();
    CarsManufactor getCarType();

    bool operator !=(const LuxuryCab &other) const;
};
#endif //EX3_LUXURYCAB_H