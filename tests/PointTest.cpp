#include "gtest/gtest.h"
#include "../Point.h"
using namespace std;
//This is a test class for the point class.
//it checks that a produced point (from given x and y) working properly.
class PointTest : public ::testing::Test {
    //those points are public members of the point test class.
public:
    Point p1;
    Point p2;
//this is a set up method for the tester (announce of the tester's beginning).
    virtual void SetUp(){
        cout << "Setting up" << endl;
    }
    //this is a tear down method for the tester (announce of the tester's ending).
    virtual void TearDown(){
        cout << "Tearing down" << endl;
    }
    PointTest():p1(1,2) , p2(3,4){}
};
//this test checks that valid inputs yields valid outputs
TEST_F(PointTest, checkIfTheInputValid){
    ASSERT_EQ(Point(1,2), p1);
    ASSERT_EQ(Point(3,4), p2);
}
//this test checks that the x and y got the expected (input) values
TEST_F(PointTest, checkTheAssingment){
    int x = p1.getX_axis();
    int y = p1.getY_axis();
    EXPECT_EQ(y, 2);
    EXPECT_EQ(x ,1);
    EXPECT_EQ(Point(3,4), p2);
    EXPECT_NE(Point(-1,2), p1);
}
//this tester checks if the x setter of the point functions appropriately.
TEST_F(PointTest, checkThePointXSetter){
    p2.setX_axis(9);
    EXPECT_NE(Point(3,4), p2);
    EXPECT_EQ(Point(9,4), p2);
}
//this tester checks if the y setter of the point functions appropriately.
TEST_F(PointTest, checkThePointYSetter){
    p2.setY_axis(9);
    EXPECT_NE(Point(3,4), p2);
    EXPECT_EQ(Point(3,9), p2);
}
