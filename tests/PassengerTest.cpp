
#include "gtest/gtest.h"
#include "../Passenger.h"
#include "../Point.h"
using namespace std;
//this is a class for testing the passenger object
//it inherits from the Test class
class PassengerTest : public ::testing::Test {
    virtual void SetUp(){
        cout << "Setting up" << endl;
    }
    virtual void TearDown(){
        cout << "Tearing down" << endl;
    }
public:
    Passenger passenger;
    PassengerTest(): passenger(Point(0,0), Point (2,2)){}
};
//check invalid inputs
TEST_F(PassengerTest, checkForInvalidInputs){
    ASSERT_GE(passenger.getSource(), Point(0,0));
    ASSERT_LE(passenger.getDestination(), Point(10,10));
    ASSERT_GE(passenger.getId(), 0);
    ASSERT_GE(passenger.getAge(), 0);
}
//check that the output from the satisfaction method is valid
TEST_F(PassengerTest, checkForInvalidOutputs){
    EXPECT_LE(passenger.satisfactionFromTrip(), 5);
    EXPECT_GE(passenger.satisfactionFromTrip(), 1);
}