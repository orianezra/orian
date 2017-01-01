
#include "gtest/gtest.h"
#include "../Cab.h"

using namespace std;
//this is a class for testing the cab
//it inherits from the Test class
class CabTest : public ::testing::Test {
    virtual void SetUp(){
        cout << "Setting up" << endl;
    }
    virtual void TearDown(){
        cout << "Tearing down" << endl;
    }
public:
    Cab cab1;
    Cab cab2;
    CabTest():cab1(1234, 0, 10, CarColors::RED,CarsManufactor::FIAT),
              cab2(5678, 1,  20, CarColors::BLUE ,CarsManufactor::HONDA){}
};
//check invalid inputs
TEST_F(CabTest, checkForInvalidInputs){
    ASSERT_GE(cab1.getID(), 0);
    ASSERT_GE(cab1.getKM(), 0);
    int type = static_cast<int>(cab1.getCarType());
    ASSERT_NE(type, 2);
    int colorNum = static_cast<int>(cab1.getColor());
    ASSERT_NE(colorNum, 1);
    ASSERT_GE(cab1.getTariff(), 0.0);
}
//check that the output is valid
TEST_F(CabTest, checkForInvalidOutputs){
    EXPECT_EQ(cab2.getID(), 5678);
    EXPECT_EQ(cab2.getKM(), 1);
    EXPECT_EQ(static_cast<int>(cab2.getCarType()), 0);
    EXPECT_EQ(static_cast<int>(cab2.getColor()), 1);
    EXPECT_EQ(cab2.getTariff(), 20);
}
//check that valid inputs yields the expected output
TEST_F(CabTest, checkForSetters) {
    cab1.setID(3456);
    ASSERT_EQ(cab1.getID(), 3456);
    cab1.setKM(5);
    ASSERT_EQ(cab1.getKM(), 5);
    cab1.setTariff(4.05);
    ASSERT_EQ(cab1.getTariff(), 4.05);
}
//check for the move method

TEST_F(CabTest, checkForMov) {
    int numOfKm = cab1.getKM();
    cab1.move(3);
    EXPECT_GT(cab1.getKM(), numOfKm);
}

