
#ifndef EX3_LISTENERCAB_H
#define EX3_LISTENERCAB_H


#include "TexiCenter.h"

class ListenerCab {
private:
    TexiCenter t;
public:
    ListenerCab();
    ~ListenerCab();
    void moveEvent(int , int);

};


#endif //EX3_LISTENERCAB_H
