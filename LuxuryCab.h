
#ifndef EX3_LUXURYCAB_H
#define EX3_LUXURYCAB_H
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
#include "CarsManufactor.h"
#include "CarColors.h"
#include "Vehicles.h"
#include "TripInfo.h"
#include "CheckPoint.h"
#include <queue>
#define BOOST_THREAD_USE_LIB
using namespace std;
using namespace boost;
using namespace boost::archive;
using namespace serialization;
//this is a class to manage a car object
//it has an id, holds and updates number of kms, and has a method for moving functionality.
class LuxuryCab : public Vehicles {
    //private members section
private:
    int id;
    int numOfKM;
    enum CarsManufactor type;
    enum CarColors color;
    double tariff;
    bool hasDriver;
    int moveByTwo;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {

        archive & boost::serialization::base_object<Vehicles>(*this);
        archive & this->id;
        archive & this->numOfKM;
        archive & this->type;
        archive & this->color;
        archive & this->tariff;
        archive & this->hasDriver;
        archive & this->moveByTwo;

    }
    //public members section
public:
    LuxuryCab();
    LuxuryCab(int, int, double, CarColors, CarsManufactor);
    ~LuxuryCab();
    int move();

    int getID();
    int getKM();
    double getTariff();
    bool hasADriver();
    void setADriver(bool b);
    void setID(int id);
    void setKM(int km);
    void setTariff(double tarif);
    void setString(string);
    void setLuxuryCab(LuxuryCab);
    int getTheMove();
    CarColors getColor();
    CarsManufactor getCarType();
    bool isA();
    bool operator !=(const LuxuryCab &other) const;
    std::string serial_str;

    void save() {
        //std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << *this;

        s.flush();
    }

    LuxuryCab load(){ //need to be change to vehicles

        boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        LuxuryCab cab;
        ia >> cab;

        return cab;
    }
};
#endif //EX3_LUXURYCAB_H