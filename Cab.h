#ifndef EX3_CAB_H
#define EX3_CAB_H

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
#include "CheckPoint.h"
#include <queue>
#include "TripInfo.h"
#include <string.h>
#define BOOST_THREAD_USE_LIB
using namespace std;
using namespace boost;
using namespace boost::archive;
using namespace serialization;
//using namespace detail;
//this is a class to manage a car object
//it has an id, holds and updates number of kms, and has a method for moving functionality.
class Cab : public Vehicles{
    //private members section
private:
    int id;
    int numOfKM;
    enum CarsManufactor type;
    enum CarColors color;
    double tariff;
    bool hasDriver;
    friend std::ostream& operator << (std::ostream& out, Cab *c)
    {
        string type = type.c_str();
        string color = color.c_str();
        out << " " << c->id << " " << c->numOfKM << " " << c->tariff << " " << type << " " << color;

        return out;
    }

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

    }

    //public members section
public:

    Cab();
    Cab(int, int, double, CarColors, CarsManufactor);
    ~Cab();
    int move(int);
    int getID();
    int getKM();
    double getTariff();
    CarColors getColor();
    CarsManufactor getCarType();
    void setID(int id);
    void setKM(int km);
    void setTariff(double tarif);
    bool hasADriver();
    void setADriver(bool b);
    bool isStandart();
    bool operator !=(const Cab &other) const;
    std::string serial_str;
    void setString(string s);
    void setCab(Cab c);
    void save() {
        //std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << *this;

        s.flush();
    }

    Cab load(){

        boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        Cab cab;
        ia >> cab;



        return cab;
     }


};

#endif //EX3_CAB_H
