
#include "gtest/gtest.h"
#include "../TexiCenter.h"
#include <iostream>
//#include "Driver.h"
//#include "TripInfo.h"
//#include "Cab.h"

using namespace std;
//this is a class for testing the texi center
//it inherits from the Test class
class TexiCenterTest : public ::testing::Test {
    virtual void SetUp(){
        cout << "Setting up" << endl;
    }
    virtual void TearDown(){
        cout << "Tearing down" << endl;
    }
public:
    TexiCenter texiCenter;
    list<Driver*> ld;
    list<Vehicles*> cb;
    list<TripInfo*> tf;
    TexiCenterTest(): texiCenter(){
    }
};

//check invalid inputs for the initialized lists.
TEST_F( TexiCenterTest, checkForInvalidInputs){
    texiCenter.setListTripI(tf);
    texiCenter.setListVehicles(cb);
    texiCenter.setListDrivers(ld);
    ASSERT_NE(texiCenter.getListVehicles().size(), 1);
    ASSERT_NE(texiCenter.getListDriver().size(), 1);
    ASSERT_NE(texiCenter.getListTrips().size(), 1);

}

//check for invalid input objects in the lists.
TEST_F(TexiCenterTest, checkForInvalidInputsForLists){
    Cab *cab2 = new Cab(1234, 0, 10, CarColors::RED,CarsManufactor::FIAT);
    texiCenter.setVehicleCab(cab2);

    //ASSERT_NE(*texiCenter.getVehicle(cab2->getID()), *cab1);
    Point* p1 = new Point(0,0);
    Point* p2 = new Point(2,2);
    Point* p = new Point(1,0);
    Point* p3 = new Point(0,2);
    TripInfo* trip2 = new TripInfo(1, 10, 1, 10.4, p , p3);
    TripInfo* trip = new TripInfo(5, 2, 1234, 13.8, p1, p2);
    texiCenter.setTripI(trip2);
    ASSERT_NE(*texiCenter.getTripI(trip2->getIdRide()), *trip);
    Driver* d = new Driver(12345678, 30, 10, MaterialStatus::WIDOWED, 0);
    Driver* d1 = new Driver(345678, 50, 10, MaterialStatus::WIDOWED, 0);
    texiCenter.setDrivers(d1);
    ASSERT_NE(*texiCenter.getDriver(d1->getId()), *d);
    delete d;
    delete trip;
    delete d1;
    delete cab2;
    delete p;
    delete p2;
    delete p1;
    delete p3;
    delete trip2;
}
//check for valid input objects in the lists.
TEST_F(TexiCenterTest, checkForValidInputsForLists) {

    Cab *cab1 = new Cab(1234, 0, 10, CarColors::RED,CarsManufactor::FIAT);
    texiCenter.setVehicleCab(cab1);
    EXPECT_EQ(texiCenter.getVehicle(cab1->getID())->getID(), 1234);

    Point* p4 = new Point(1,1);
    Point* p5 = new Point(1,2);
    TripInfo* trip3 = new TripInfo(12, 10, 12, 10.4, p4 , p5);
    texiCenter.setTripI(trip3);
    //EXPECT_EQ(texiCenter.getTripI(trip3->getIdRide())->getIdRide(), 12);

    Driver* d1 = new Driver(345678, 50, 10, MaterialStatus::WIDOWED, 0);
    texiCenter.setDrivers(d1);
    EXPECT_EQ(texiCenter.getDriver(d1->getId())->getId(), 345678);

    delete d1;
    delete cab1;
    delete p4;
    delete p5;
    delete trip3;
}
/*
//check for the getCall method
TEST_F( TexiCenterTest, checkForInvalidOutputsCall){
    int sizeBeforeAdd = texiCenter.getListTrips().size();
    texiCenter.getCall(Point(0,0), Point(2,2));

    Driver* d = new Driver(12345678, 30, 10,MaterialStatus::SINGLE, 0);
    d->setLocation(Point(1,1));
    texiCenter.setDrivers(d);

    EXPECT_GT(texiCenter.getListTrips().size(), sizeBeforeAdd);
    //list<TripInfo*> t = texiCenter.getListTrips();
    TripInfo* t2 = t.back();
    EXPECT_EQ(t2->getEndPoint()->getX_axis(),2);
    EXPECT_EQ(t2->getEndPoint()->getY_axis(),2);
    EXPECT_EQ(t2->getStartPoint()->getX_axis(), 0);
    EXPECT_EQ(t2->getStartPoint()->getY_axis(), 0);
    delete trip;
    delete d;
}*/
