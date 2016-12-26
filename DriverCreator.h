//
// Created by orian on 12/14/16.
//

#ifndef EX3_DRIVERCREATOR_H
#define EX3_DRIVERCREATOR_H

#include "Driver.h"
#include <cstdlib>
#include "MaterialStatus.h"
class DriverCreator {
public:
    Driver* createNewDriver(string input);
    DriverCreator();
    ~DriverCreator();
};


#endif //EX3_DRIVERCREATOR_H
