//
// Created by orian on 12/14/16.
//

#include "DriverCreator.h"
DriverCreator::DriverCreator() {}
DriverCreator::~DriverCreator(){}
Driver* DriverCreator::createNewDriver(string input) {
    unsigned int i = 0;
    int arr[2];
    int j = 0;
    MaterialStatus m;
    while (i < input.size()) {
        if (input.at(i) != ',') {
            if (isdigit(input.at(i))) {
                arr[j] = atoi(input.c_str() + i);
                if (arr[j] > 9) {
                    i++;
                }

            } else {
                switch (input.at(i)) {
                    case 'S' : {
                        m = MaterialStatus::SINGLE;
                        break;
                    }
                    case 'M' : {
                        m = MaterialStatus::MARRIED;
                        break;
                    }
                    case 'D' : {
                        m = MaterialStatus::DIVORCED;
                        break;
                    }
                    case 'W' : {
                        m = MaterialStatus::WIDOWED;
                        break;
                    }

                }
            }
            j++;
        }
        i++;

    }
            int id = arr[0];
            int age = arr[1];
            cout << age << endl;
            int yearsOfExp = arr[3];
            int veichleId = arr[4];
        return new Driver(id, age, yearsOfExp, m, veichleId);

}