#ifndef EX3_VEHICLES_H
#define EX3_VEHICLES_H
#include "CarsManufactor.h"
#include "CarColors.h"
#include "TripInfo.h"
#include "CheckPoint.h"
#include <queue>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
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
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>


#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
//this is an abstract class for a vehicle.
//it has a move method for the moving functionality/

using namespace std;
using namespace boost::archive;
//using namespace serialization;
//this is an abstract class for a vehicle.
//it has a move method for the moving functionality/
class Vehicles {
    //public members section

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version){}

public:
    virtual int move()=0;
    virtual bool isA() = 0;
    virtual int getID() = 0;

    virtual int getKM() = 0;

    virtual CarColors getColor() = 0;

    virtual CarsManufactor getCarType() = 0;

    virtual void setID(int) = 0;

    virtual void setKM(int) = 0;

    virtual double getTariff() = 0;

    virtual void setTariff(double) = 0;

    virtual void setADriver(bool) = 0;

    virtual bool hasADriver() = 0;
    virtual int getTheMove()=0;
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Vehicles)
#endif //EX3_VEHICLES_H