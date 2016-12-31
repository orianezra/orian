//
// Created by orian on 12/6/16.
//

#ifndef EX3_CHECKPOINT_H
#define EX3_CHECKPOINT_H
/*
 * This class's purpose is to manage a CheckPoint object.
 * It wraps a point and add the information whether this point
 * was touched or not.
 */
#include "Point.h"
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
using namespace std;
using namespace boost;
using namespace boost::archive;
using namespace serialization;
class CheckPoint : public Point {
    //private member section.
private:
    bool isTouched;
    bool isExist;
    bool firstNeighbor;
    bool secondNeighbor;
    bool thirdNeighbor;
    bool forthNeighbor;
    friend std::ostream& operator << (std::ostream& out, CheckPoint *c)
    {
        out << "(" << c->x_axis << "," << c->y_axis<< ")";
        return out;
    }
    friend class boost::serialization::access;
    template<class Archive>

    void serialize(Archive& archive, const unsigned int version)
    {

        archive & boost::serialization::base_object<Point>(*this);
        archive & this->x_axis;
        archive & this->y_axis;

    }

    //public member section.
public:
    void setFirstNeighbor(bool);
    void setSecondNeighbor(bool);
    void setThirdNeighbor(bool);
    void setForthNeighbor(bool);
    bool isFirstNeighborExist();
    bool isSeondNeighborExist();
    bool isThirdNeighborExist();
    bool isForthNeighborExist();
    void exisSetBool();
    bool exisGetBool();
    void setIsToched();
    bool getIsTouchd();
    CheckPoint();
    CheckPoint(int x, int y);
    ~CheckPoint();
    int getX_axis();
    int getY_axis();
    bool operator <=(const CheckPoint &other) const;
    bool operator >=(const CheckPoint &other) const;
    bool operator ==(const CheckPoint &point) const;
    bool operator !=(const CheckPoint &other) const;
    std::string serial_str;

    void save() {
        //std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << *this;

        s.flush();
    }

    CheckPoint load(){

        boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        CheckPoint check;
        ia >> check;

        return check;
    }
};

#endif //EX3_CHECKPOINT_H
