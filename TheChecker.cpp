//
// Created by orian on 1/29/17.
//

#include "TheChecker.h"
TheChecker::TheChecker(){}
TheChecker::~TheChecker(){}
Map* TheChecker::createMap() {
    int x,y,pOfAbs;
    Grid* g;
    Map* m;
    bool invalidInput;
    do {
        string input;
        cin.clear();
        getline(cin, input);
        invalidInput = false;
        size_t found = input.find_first_not_of(" ");
        string inputFixedSpaces = input.substr(found);
        size_t findMiddle = inputFixedSpaces.find(' ');
        if (findMiddle == -1) {
            cout << "-1" << endl;
            invalidInput = true;
            continue;
        }
        string xStr = inputFixedSpaces.substr(0, findMiddle).c_str();
        string yStr = inputFixedSpaces.substr(findMiddle + 1).c_str();
        x = atoi(xStr.c_str());
        y = atoi(yStr.c_str());
        if ( (x == 0 && xStr.at(0) != '0') ||(y == 0 && yStr.at(0) != '0')) {
            cout << "-1" << endl;
            invalidInput = true;
            continue;
        }
        if ( x <= 0 || y <= 0) {
            cout << "-1" << endl;
            invalidInput = true;
            continue;
        } else {
            g = new Grid(x, y);
            m = new Map(g);
            string inputObstacles;
            cin.clear();
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, inputObstacles);
            pOfAbs = atoi(inputObstacles.c_str());
            if (pOfAbs == 0 && inputObstacles.at(0) != '0') {
                cout << "-1" << endl;
                invalidInput = true;
                continue;
            }

            if (pOfAbs < 0) {
                cout << "-1" << endl;
                invalidInput = true;
                continue;
            } else {
                while (pOfAbs > 0) {
                    string inputObstacles;
                    cin.clear();
                    getline(cin, inputObstacles);
                    size_t findMiddle = inputObstacles.find(',');
                    if (findMiddle == -1) {
                        cout << "-1" << endl;
                        invalidInput = true;
                        break;
                    }
                    string xStr = inputObstacles.substr(0, findMiddle);
                    string yStr = inputObstacles.substr(findMiddle + 1);
                    x = atoi(xStr.c_str());
                    y = atoi(yStr.c_str());
                    if ( (x == 0 && xStr.at(0) != '0') ||(y == 0 && yStr.at(0) != '0')) {
                        cout << "-1" << endl;
                        invalidInput = true;
                        break;
                    }
                    if (x >= m->getGrid()->getX() || y >= m->getGrid()->getY() || x < 0 || y < 0){
                        cout << "-1" << endl;
                        invalidInput = true;
                        break;
                    }
                    m->createO(Point(x, y));
                    pOfAbs--;
                }

            }
        }
    } while (invalidInput);
}