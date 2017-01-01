#ifndef EX3_TRIPINFO_H
#define EX3_TRIPINFO_H
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <list>
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
#include <boost/serialization/list.hpp>
using namespace std;
using namespace boost;
using namespace boost::archive;
using namespace serialization;
#include "CheckPoint.h"
//this class's purpose is to manage trip info object
//it holds information about a trip
class TripInfo {
    //private member section
private:
    int rideId;
    int mettersPass;
    Point* startP;
    Point* endP;
    double tariff;
    int numOfPassengers;
    unsigned long timeOfTrip;
    list<CheckPoint*> way;
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& archive, const unsigned int version)
    {
        archive & this->rideId;
        archive & this->mettersPass;
        archive & this->startP;
        archive & this->endP;
        archive & this->tariff;
        archive & this->numOfPassengers;
        archive & this->timeOfTrip;
        archive & this->way;
    }
    //public member section
public:
    TripInfo(int mP, int nP, int rID, double t, Point* sP, Point* eP, unsigned long);
    TripInfo();
    ~TripInfo();
    void setIdRide(int);
    void setMetters(int);
    void setNumOfPassangers(int);
    void setTarif(double);
    void setEndPoint(Point*);
    void setStartPoint(Point*);
    int getIdRide();
    int getMetters();
    int getNumOfPassangers();
    double getTarif();
    Point* getEndPoint();
    Point* getStartPoint();
    bool operator !=(const TripInfo &other) const;
    std::string serial_str;
    void setTripInfo(TripInfo);
    void setString(string s);
    list<CheckPoint*> convertToListInit(queue<CheckPoint*> wayQueue);
    unsigned long getTimeOfTrip();
    void save() {
        boost::iostreams::back_insert_device<std::string> inserter(serial_str);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
        boost::archive::binary_oarchive oa(s);
        oa << *this;

        s.flush();
    }

    TripInfo load(){
        boost::iostreams::basic_array_source<char> device(serial_str.c_str(), serial_str.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        TripInfo trip;
        ia >> trip;

        return trip;
    }

};

#endif //EX3_TRIPINFO