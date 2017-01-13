//
// Created by orian on 1/13/17.
//
#include "Information.h"
Information::Information() {}

Information::~Information() {}

Information::Information(Tcp* c, TexiCenter *t, int *num) {
    this->texiC = t;
    this->numOfDrivers = num;
    this->tcp = c;
}

void Information::setTcp(Tcp *tcp) {
    this->tcp = tcp;
}

Tcp* Information::getTcp(){
    return this->tcp;
}

TexiCenter*  Information::getTexiC(){
    return this->texiC;
}

int*  Information::getNumOfDrivers(){
    return this->numOfDrivers;
}