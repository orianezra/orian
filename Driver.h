
#ifndef EX3_DRIVER_H
#define EX3_DRIVER_H
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/detail/archive_serializer_map.hpp>
#include <boost/archive/detail/basic_iarchive.hpp>
#include <boost/archive/detail/basic_oarchive.hpp>
#include <boost/archive/detail/basic_iserializer.hpp>
#include <boost/archive/detail/basic_serializer.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include "Person.h"
#include "Cab.h"
#include "LuxuryCab.h"
#include "Gps.h"
#include "MaterialStatus.h"
#include "Map.h"
using namespace std;
using namespace boost;
using namespace boost::archive;
using namespace serialization;
//this class's purpose is to manage a driver object.
//it inherits from person, and has the functionality of having a car.
class Driver : public Person {
    //private members section
private:
    int id;
    int age;
    MaterialStatus status;
    int yearsOfEp;
    int avgSatisfaction;
    Vehicles* texiInfo;
    Gps* waze;
    Point location;
    Map* map;
    bool existCar;
    TripInfo* trip;
    int cabId;
    friend class boost::serialization::access;
    template<class Archive>
    //this is a serialize method
    void serialize(Archive& archive, const unsigned int version)
    {

        archive & boost::serialization::base_object<Person>(*this);
        archive & this->id;
        archive & this->age;
        archive & this->cabId;
        archive & this->status;
        archive & this->yearsOfEp;
        archive & this->avgSatisfaction;
        archive & this->texiInfo;
        archive & this->location;
        //archive & this->waze;
        archive & this->map;
        archive & this->existCar;
        archive & this->trip;

    }
    //public members section
public:
    void setLocation(Point);
    Point getLocation();

    Driver(int, int, int, MaterialStatus, int);
    Driver();
    virtual ~Driver();
    void setTripInfo(TripInfo*);
    TripInfo* getTripInfo();
    void setTexi(Vehicles* c);
    Vehicles* getTexiOfDriver();
    void setMap(Map*);
    Map* getMap();
    void drive(CheckPoint*);
    int getAge();
    int getId();
    int getCabId();
    void setGps(Gps* g);
    Gps* getGps();
    bool getExist();
    int getSatisfaction();
    MaterialStatus getStatus();
    int getYearsOfExperiance();
    void setStatus(MaterialStatus status);
    void setSatisfaction(int st);
    bool operator !=(const Driver &other) const;
    unsigned long disCalculation(Point other);
    std::string serial_str;
    void setDriver(Driver d);
    void setString(string);
    //this is a save method for serialization
    void save() {
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << *this;

        s.flush();
    }
    //this is a load method for deserialization
    Driver load(){

        boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        Driver d;
        ia >> d;

        return d;
    }

};

#endif //EX3_DRIVER_H