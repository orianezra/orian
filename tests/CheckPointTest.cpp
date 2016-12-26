
#include "gtest/gtest.h"
#include "../CheckPoint.h"
using namespace std;
//this is a class for testing the check point class
//it inherits from the Test class
class CheckPointTest : public ::testing::Test {
protected:

    virtual void SetUp(){
        cout << "Setting up" << endl;
    }
    virtual void TearDown(){
        cout << "Tearing down" << endl;

    }
public:
    CheckPoint p1;
    CheckPoint p3;
    CheckPoint p2;
    CheckPointTest():p1(1,2) , p2(3,4), p3(6,6){}
};
//check invalid inputs
TEST_F(CheckPointTest, checkForInvalidInputs){
    ASSERT_LE(p1, CheckPoint(10,10));
    ASSERT_LE(p2, CheckPoint(10,10));
    ASSERT_LE(p3, CheckPoint(10,10));
    ASSERT_GE(p1, CheckPoint(0,0));
    ASSERT_GE(p2, CheckPoint(0,0));
    ASSERT_GE(p3, CheckPoint(0,0));
}
//check that valid inputs yields valid outputs
TEST_F(CheckPointTest, checkForInvalidValues) {
    ASSERT_EQ(Point(1,2), p1);
    ASSERT_EQ(Point(3,4), p2);
}
//this test checks that the x and y got the expected (input) values
TEST_F(CheckPointTest, checkForInvalidOutputs) {
    int x = p1.getX_axis();
    int y = p1.getY_axis();
    EXPECT_EQ(y, 2);
    EXPECT_EQ(x ,1);
    EXPECT_EQ(Point(3,4), p2);
    EXPECT_NE(Point(-1,2), p1);
    EXPECT_NE(p3, p2);
}
//check for invalid outputs (x) from valid inputs
TEST_F(CheckPointTest, checkForInvalidOutputsY) {
    p2.setX_axis(9);
    EXPECT_NE(Point(3,4), p2);
    EXPECT_EQ(Point(9,4), p2);
}
//check for invalid outputs (y) from valid inputs
TEST_F(CheckPointTest, checkForInvalidOutputsX) {
    p2.setY_axis(9);
    EXPECT_NE(Point(3,4), p2);
    EXPECT_EQ(Point(3,9), p2);
}
//test the boolean functions
TEST_F(CheckPointTest, checkForBooleans) {
    EXPECT_EQ(p1.exisGetBool(), true);
    EXPECT_EQ(p1.isFirstNeighborExist(), false);
    EXPECT_EQ(p1.isSeondNeighborExist(), false);
    EXPECT_EQ(p1.isForthNeighborExist(), false);
    EXPECT_EQ(p1.isThirdNeighborExist(), false);
}