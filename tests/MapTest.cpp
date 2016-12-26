#include "gtest/gtest.h"
#include "../Map.h"
using namespace std;
//this is a class for testing the map
//it inherits from the Test class
class MapTest : public ::testing::Test {
    virtual void SetUp(){
        cout << "Setting up" << endl;
    }
    virtual void TearDown(){
        cout << "Tearing down" << endl;
        delete g;
    }
public:
    Map map;
    Grid* g;
    MapTest(): map(g = new Grid(4, 4)){}
};
//check invalid inputs
TEST_F( MapTest, checkForInvalidInputs){
    list<Point> pL;
    pL.push_back(Point(2,1));
    pL.push_back(Point(2,3));
    //check the createO method
    map.createO(Point(1,1));
    Grid* gDummy = map.getGrid();
    gDummy->giving(pL.front().getX_axis(),pL.front().getY_axis())->exisSetBool();
    bool bP = gDummy->giving(pL.front().getX_axis(),pL.front().getY_axis())->exisGetBool();
    ASSERT_FALSE(bP);
    CheckPoint* cP = gDummy->giving(pL.front().getX_axis(),pL.front().getY_axis());
    ASSERT_NE(*cP, CheckPoint(2,3));
    delete gDummy;
}
//check valid inputs
TEST_F( MapTest, checkForValidInputs){
    list<Point> pL;
    pL.push_back(Point(2,1));
    pL.push_back(Point(2,3));
    //check the createO method
    map.createO(Point(1,1));
    Grid* gDummy1 = map.getGrid();
    gDummy1->giving(pL.front().getX_axis(),pL.front().getY_axis())->exisSetBool();
    bool bP = gDummy1->giving(pL.front().getX_axis(),pL.front().getY_axis())->exisGetBool();
    EXPECT_FALSE(bP);
    CheckPoint* cP = gDummy1->giving(pL.front().getX_axis(),pL.front().getY_axis());
    EXPECT_EQ(*cP, CheckPoint(2,1));
    delete gDummy1;
}
