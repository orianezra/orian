
#include "Map.h"
//this is the default constructor of the map class
Map::Map() {
}
//this is the constructor of the map class
Map::Map(Grid* g){


    this->g=g;
}

//this is the destructor of the map class
Map::~Map() {

}
//this mathod creates a copy of the map's grid and return it
Grid* Map:: getGrid(){
    Grid* gCopy = new Grid(this->g->getX(), this->g->getY());
    return this->createO(this->getListOfO(), gCopy);
}
//this is a getter method for the map's list of obstacles
list<Point> Map::getListOfO() {
    return this->oP;
}

//this a method for creating a map (adding forbidden points to a given grid)
void Map::createO(Point p){
    this->oP.push_front(p);
    this->g->giving(p.getX_axis(), p.getY_axis())->exisSetBool();
}
//this a method for creating a map (adding forbidden points to a given grid)
Grid* Map::createO(list<Point> l, Grid* gC){
    for(int i = 0; i<l.size();i++){
        Point p = l.front();
        l.pop_front();
        gC->giving(p.getX_axis(),p.getY_axis())->exisSetBool();
        l.push_back(p);
    }
    return gC;
}