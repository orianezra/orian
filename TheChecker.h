//
// Created by orian on 1/29/17.
//

#ifndef EX3_THECHECKER_H
#define EX3_THECHECKER_H
#include "Map.h"
//This is a class for the input validation checks.
//this class contains methods that will check the input and create objects appropriately.
class TheChecker {
public:
    TheChecker();
    ~TheChecker();
    Map* createMap();
};


#endif //EX3_THECHECKER_H
