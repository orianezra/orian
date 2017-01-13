//
// Created by orian on 1/13/17.
//
#ifndef EX3_INFORMATION_H
#define EX3_INFORMATION_H

#include "Tcp.h"
#include "TexiCenter.h"

class Information {
private:
    Tcp* tcp;
    TexiCenter* texiC;
    int* numOfDrivers;
public:
    Information();
    ~Information();
    Information(Tcp*,TexiCenter*, int*);
    void setTcp(Tcp*);
    Tcp* getTcp();
    TexiCenter* getTexiC();
    int* getNumOfDrivers();
};


#endif //EX3_INFORMATION_H