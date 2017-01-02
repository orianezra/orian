
#include <iostream>
#include <string>
#include <unistd.h>
#include "Udp.h"
#include "Cab.h"
#include "Driver.h"
#include <cstdlib>
using namespace std;
using namespace boost;
int main(int argc, char *argv[]) {
        Udp udpClient(0, atoi(argv[1]));
        udpClient.initialize();
        char dummy, status;
        MaterialStatus materialStatus;
        int id, age, exp, vehicleId;
        cin >> id >> dummy >> age  >> dummy >>status >> dummy >> exp >> dummy >>vehicleId;
        switch(status){
                case 'S' : {
                        materialStatus = MaterialStatus :: SINGLE;
                        break;
                }
                case 'M' : {
                        materialStatus = MaterialStatus :: MARRIED;
                        break;
                }
                case 'D' : {
                        materialStatus = MaterialStatus :: DIVORCED;
                        break;
                }
                case 'W' : {
                        materialStatus = MaterialStatus :: WIDOWED;
                        break;
                }
                default: {
                        cout << "status not exist" << endl;
                        break;
                }
        }
        Driver* driver = new Driver(id, age, exp, materialStatus, vehicleId);

        driver->save();
        udpClient.sendData(driver->serial_str);
        char bufferMap[80000];
        udpClient.reciveData(bufferMap, sizeof(bufferMap));
        char buffer[2000];
        udpClient.reciveData(buffer, sizeof(buffer));
        string stMess(buffer);
        cout << stMess <<endl;
        char buffer2[1];
        udpClient.reciveData(buffer2, sizeof(buffer));//this is for getting the cars type
        string stCarType(buffer2);
        if(stCarType == "1") {
                udpClient.reciveData(buffer, sizeof(buffer));
                string stMessCab(buffer, sizeof(buffer));
                Cab cabDummy;
                cabDummy.setString(stMessCab);
                Cab* cabO = new Cab();
                cabO->setCab(cabDummy.load());
                driver->setTexi(cabO);
                udpClient.sendData("we got the cab!");
        } else {
                udpClient.reciveData(buffer, sizeof(buffer));
                string stMessCab(buffer, sizeof(buffer));
                LuxuryCab cabDummy;
                cabDummy.setString(stMessCab);
                LuxuryCab* luxuryCabO = new LuxuryCab();
                luxuryCabO->setLuxuryCab(cabDummy.load());
                driver->setTexi(luxuryCabO);
                udpClient.sendData("we got the luxurycab!");
        }

        //calculate distance according to the driver's location and start point of the trip
        //move the driver
        char buffer0[2000];
        udpClient.reciveData(buffer0, sizeof(buffer0));
        string stMessage(buffer0);
        TripInfo* t= new TripInfo();
        if (stMessage.compare("start triping shimi") == 0) {
                char buffer1[40000];
                udpClient.reciveData(buffer1, sizeof(buffer1));
                string stMessTrip(buffer1, sizeof(buffer1));
                TripInfo tDummy;
                tDummy.setString(stMessTrip);
                t->setTripInfo(tDummy.load());
                driver->setTripInfo(t);
                udpClient.sendData("we got shimi's job!! :)");
        }


        char buffer4[1024];
        udpClient.reciveData(buffer4, sizeof(buffer4));
        string stTime(buffer4);
        unsigned long time = strtoul(stTime.c_str(), NULL, 0);
        if (time == driver->getTripInfo()->getTimeOfTrip()) {
            CheckPoint* p  = driver->getTripInfo()->getWay().front();
            //set location of the driver
            //move the cab (km++)
            //update trip info (km++)
        }

}