
#ifndef EX3_PERSON_H
#define EX3_PERSON_H
#include <string>
#include <stdlib.h>
using namespace std;
//this is an abstract class for a person.
//it has an id and age.
class Person {
//public member section
public:
    virtual int getAge()= 0;
    virtual int getId()= 0;
};
#endif //EX3_PERSON_H
