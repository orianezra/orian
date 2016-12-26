
#include "gtest/gtest.h"
#include "../TripInfo.h"
//#include "CheckPoint.h"
using namespace std;
//this is a tester for the trip info class
//it inherits from the Test class
class TripInfoTest : public ::testing::Test {
    virtual void SetUp(){
        cout << "Setting up" << endl;
    }
    virtual void TearDown(){
        cout << "Tearing down" << endl;
        delete p1;
        delete p2;
    }
public:
    TripInfo trip;
    Point* p1;
    Point* p2;
    TripInfoTest(): trip(5, 2, 1234, 13.8, p1 = new Point(0,0), p2 = new Point(2,2)){}
};
//check invalid inputs
TEST_F(TripInfoTest, checkForInvalidInputs){
    ASSERT_GT(trip.getIdRide(), 0);
    ASSERT_GT(trip.getNumOfPassangers(), 0);
    ASSERT_GE(trip.getMetters(), 0);
    ASSERT_GE(trip.getTarif(), 0);
    Point* pStart = new Point(0,0);
    Point* pEnd = new Point(10,10);
    ASSERT_GE(*trip.getStartPoint(), *pStart);
    ASSERT_LE(*trip.getEndPoint(), *pEnd);
    delete pStart;
    delete pEnd;
}
//check that the output is valid
TEST_F(TripInfoTest, checkForInvalidOutputs){
    ASSERT_EQ(trip.getIdRide(), 1234);
    Point* pStart = new Point(0,0);
    Point* pEnd = new Point(2,2);
    ASSERT_EQ(*trip.getEndPoint(), *pEnd);
    ASSERT_EQ(*trip.getStartPoint(), *pStart);
    ASSERT_EQ(trip.getTarif(), 13.8);
    ASSERT_EQ(trip.getNumOfPassangers(), 2);
    ASSERT_EQ(trip.getMetters(), 5);
    delete pStart;
    delete pEnd;
}
