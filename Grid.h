#ifndef EX3_GRID_H
#define EX3_GRID_H
#include "CheckPoint.h"
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
#include <boost/serialization/array.hpp>
using namespace std;
using namespace boost;
using namespace boost::archive;
using namespace serialization;
/*
 * This class's purpose is to manage a Grid object.
 * The grid is a two dimensional array, which is composed from CheckPoints.
 */
class Grid {
    //private member section.
private:
    int x;
    int y;
    CheckPoint* arr[1000][1000];
    friend std::ostream& operator << (std::ostream& out, Grid *g)
    {
        out << g->x << "_" << g->y;
        return out;
    }
    friend class boost::serialization::access;
    template<class Archive>
    //this is a serialize method
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & this->x;
        archive & this->y;
        archive & this->arr;
    }

    //public member section.
public:
    Grid();
    int getX();
    int getY();

    Grid(int x, int y);
    ~Grid();
    void maker();
    CheckPoint * giving(int xCor, int yCor);
    std::string serial_str;
    //this is a save method for serialization
    void save() {
        //std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << *this;

        s.flush();
    }
    //this is a method for deserialization
    Grid load(){

        boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        Grid grid;
        ia >> grid;

        return grid;
    }

};


#endif //EX3_GRID_H
