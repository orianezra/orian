
#include "gtest/gtest.h"
#include "../Grid.h"
using namespace std;
//this is a class for testing the grid class
//it inherits from the Test class
class GridTest : public ::testing::Test {
	//a method for setting up the grid tester
	virtual void SetUp(){
		cout << "Setting up" << endl;
	}
	//a method for tearing down the grid tester
	virtual void TearDown(){
		cout << "Tearing down" << endl;

	}
public:
	Grid grid1;
	Grid grid2;
	GridTest(): grid1(4,4), grid2(1,10){}
};
//check invalid inputs for the grid`s
TEST_F(GridTest, checkForInvalidInputs){
	ASSERT_LE(grid1.getX(), 10);
	ASSERT_LE(grid1.getY(), 10);
	ASSERT_GE(grid1.getX(), 0);
	ASSERT_GE(grid1.getY(), 0);

	ASSERT_LE(grid2.getX(), 10);
	ASSERT_LE(grid2.getY(), 10);
	ASSERT_GE(grid2.getX(), 0);
	ASSERT_GE(grid2.getY(), 0);
}
//check valid inputs for the grid`s
TEST_F(GridTest, checkForvalidInputs){
	ASSERT_EQ(grid1.getX(), 4);
	ASSERT_EQ(grid1.getY(), 4);

	ASSERT_EQ(grid2.getX(), 1);
	ASSERT_EQ(grid2.getY(), 10);
}
//check that valid input yields expected output
TEST_F(GridTest, checkForValidGivingFunc){
	CheckPoint* cPoint = new CheckPoint(1,3);
	ASSERT_NE(*grid1.giving(2,2), *cPoint);
	EXPECT_EQ(*grid1.giving(1,3), *cPoint);

	delete cPoint;
}
//check the validation of the grid
TEST_F(GridTest, checkForValidGrid){
	for(int i = 0; i < grid1.getX(); i++){
		for(int j = 0; j < grid1.getY(); j++) {
			CheckPoint* cPoint = new CheckPoint(i,j);
			ASSERT_EQ(*grid1.giving(i,j), *cPoint);
			delete cPoint;
		}
	}
}