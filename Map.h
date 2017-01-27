
#ifndef EX3_MAP_H
#define EX3_MAP_H
#include "Grid.h"
#include <list>
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
#include <boost/serialization/list.hpp>

using namespace std;
using namespace boost;
using namespace boost::archive;
using namespace serialization;
//this class's purpose is to manage a map object.
//it holds a grid and adds to it some forbidden points
class Map {
    //private member section
private:
    Grid* g;
    Point p;
    list<Point> oP;
    friend std::ostream& operator << (std::ostream& out, Map *m)
    {
        out << m->g->getX() << "X" << m->g->getY();
        out << "obstaces are at:";
        list<Point> obstacles = m->getListOfO();
        for (int i = 0; i < m->oP.size(); i++) {
            out << "(" << m->getListOfO().front().getX_axis() << ","
                << m->getListOfO().front().getY_axis() << ")";
            obstacles.pop_front();
        }
        return out;
    }
    friend class boost::serialization::access;
    template<class Archive>
    //this is a method for serialization
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & this->g;
        archive & this->p;
        archive & this->oP;
    }
    //public members section
public:
    Map(Grid* g);
    Map();
    ~Map();
    Grid* getGrid();
    Grid* createO(list<Point>, Grid*);
    list<Point> getListOfO();
    void createO(Point);
    std::string serial_str;
    //this is a method for serialization
    void save() {
        //std::string serial_str;
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << *this;

        s.flush();
    }
    //this is a method for deserialization
    Map load(){

        boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        Map map;
        ia >> map;

        return map;
    }
};

#endif //EX3_MAP_