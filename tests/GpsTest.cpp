
#include "gtest/gtest.h"
#include "../Gps.h"
using namespace std;
//this is a class for testing the GPS class
//it inherits from the Test class
class GpsTest : public ::testing::Test {
protected:
    virtual void SetUp(){
      cout << "Setting up" << endl;
    }
    virtual void TearDown(){
      cout << "Tearing down" << endl;
      delete p1;
      delete p2;

    }
public:
    Gps gps1;
    Point* p1;
    Point* p2;
    GpsTest(): gps1(p1 = new Point(0,0), p2 = new Point(2,2)){}
};
//testing the ask neighbor method
TEST_F(GpsTest, checkForInvalidOutputsAskNe){
  ASSERT_LE(gps1.getStart()->getX_axis(), 10);
  ASSERT_LE(gps1.getStart()->getY_axis(), 10);
  ASSERT_GE(*gps1.getStart(), Point(0,0));
  ASSERT_LE(*gps1.getEnd(), Point(10,10));
  EXPECT_EQ(*gps1.getStart(), Point(0,0));
  EXPECT_EQ(*gps1.getEnd(), Point(2,2));
  CheckPoint* c = new CheckPoint(1,1);
  EXPECT_EQ(gps1.askNE(*c), false);
  delete c;
}
//testing the start method and return path method.
TEST_F(GpsTest, checkForInvalidOutputs) {
  Grid* grid = new Grid(3,3);
  queue<CheckPoint*> queue= gps1.start(grid);
  CheckPoint* cP = queue.front();
  queue.pop();
  CheckPoint* cP2 = queue.front();
  //cout<< cP->getX_axis() <<  "," << cP->getY_axis() << endl;
  ASSERT_GT(queue.size(), 0);
  EXPECT_FALSE(cP2->isFirstNeighborExist());
  EXPECT_TRUE(cP2->isSeondNeighborExist());
  //EXPECT_EQ(cP2->isThirdNeighborExist(), false);
  EXPECT_NE(cP2->isForthNeighborExist(), true);
  EXPECT_EQ(queue.size(), 4);
  delete grid;
}
//testing the return path method
TEST_F(GpsTest, checkForInvalidOutputsPath) {
  Grid* grid = new Grid(3,3);
  queue<CheckPoint*> queue1= gps1.start(grid);
  queue<CheckPoint*> queue2 = gps1.returnPath(grid, queue1);
  EXPECT_EQ(queue1.size(), queue2.size());
  delete grid;
}