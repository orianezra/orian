#include "gtest/gtest.h"
#include "../Driver.h"
#include "../MaterialStatus.h"
using namespace std;
//this is a class for testing the driver class
//it inherits from the Test class
class DriverTest : public ::testing::Test {
    virtual void SetUp(){
        cout << "Setting up" << endl;
    }
    virtual void TearDown(){
        cout << "Tearing down" << endl;
    }
public:
    Driver driver;
    DriverTest(): driver(12345678, 30, 10, MaterialStatus::WIDOWED, 0){}
};
//check invalid inputs
TEST_F( DriverTest, checkForInvalidInputs){
    ASSERT_GE(driver.getId(), 0);
    ASSERT_GE(driver.getAge(), 0);
    ASSERT_NE(driver.getSatisfaction(), 1);
    int status = static_cast<int>(driver.getStatus());
    ASSERT_NE(status, 2);
    ASSERT_GE(driver.getYearsOfExperiance(), 0);
}
//check driver output is valid
TEST_F (DriverTest, checkForInvalidOutputs){
    EXPECT_EQ(driver.getId(), 12345678);
    EXPECT_EQ(driver.getAge(), 30);
    EXPECT_EQ(driver.getSatisfaction(), 0);
    EXPECT_EQ(driver.getYearsOfExperiance(), 10);
    EXPECT_EQ(static_cast<int>(driver.getStatus()), 3);
}
//check that cab valid inputs yields the expected output
TEST_F(DriverTest, checkForSetters) {
    driver.setStatus(MaterialStatus::DIVORCED);
    EXPECT_EQ(static_cast<int>(driver.getStatus()), 2);
    Cab* cab = new Cab(1234, 0, 10.0, CarColors::RED, CarsManufactor::FIAT);
    driver.setTexi(cab);
    EXPECT_EQ(driver.getTexiOfDriver()->getID(), 1234);
    EXPECT_EQ(driver.getTexiOfDriver()->getKM(), 0);
    EXPECT_EQ(driver.getTexiOfDriver()->getTariff(), 10.0);
    EXPECT_EQ(static_cast<int>(driver.getTexiOfDriver()->getColor()), 0);
    EXPECT_EQ(static_cast<int>(driver.getTexiOfDriver()->getCarType()), 3);
    delete cab;
}
//check for the GPS setting
TEST_F(DriverTest, checkForGps) {
    Gps* gps = new Gps( new Point(0,0), new Point(2,2));
    driver.setGps(gps);
    EXPECT_EQ(driver.getGps()->getStart()->getX_axis(), 0);
    EXPECT_EQ(driver.getGps()->getEnd()->getX_axis(), 2);
    delete gps;
}