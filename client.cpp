
#include <iostream>
#include <string>
#include <unistd.h>
//#include "Udp.h"
#include "Cab.h"
#include "Driver.h"
#include "Tcp.h"

#include "MaterialStatus.h"
using namespace std;

int main(int argc, char *argv[]) {
    //initiallize udp for message getting
    Tcp tcpClient(0, atoi(argv[2]));
    //tcpClient.initialize();
    char dummy, status;

    MaterialStatus materialStatus;
    int id, age, exp, vehicleId;
    cin >> id >> dummy >> age  >> dummy >>status >> dummy >> exp >> dummy >>vehicleId;
    if (id < 0 || age <0 || exp < 0 || vehicleId < 0){
        exit(-1);
    }
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
            exit(-1);
        }
    }
    Driver* driver = new Driver(id, age, exp, materialStatus, vehicleId);
    tcpClient.initialize();
    char buffer0[2000];
    tcpClient.reciveData(buffer0, sizeof(buffer0));
    string stMess0(buffer0);
    cout << stMess0 << endl;//getting shimi


    driver->save();
    sleep(1);
    tcpClient.sendData(driver->serial_str);
    char buffer[2000];
    tcpClient.reciveData(buffer, sizeof(buffer));
    string stMess(buffer);
    cout << stMess <<endl;//thenks for
    char buffer2[10];
    tcpClient.reciveData(buffer2, sizeof(buffer2));//this is for getting the cars type
    string stCarType(buffer2);

    if(stCarType.at(0) = '1') {
        //set the driver's cab
        sleep(1);
        tcpClient.sendData("getting cab");
        tcpClient.reciveData(buffer, sizeof(buffer));
        string stMessCab(buffer, sizeof(buffer));
        Cab cabDummy;

        cabDummy.setString(stMessCab);
        Cab* cabO = new Cab();
        cabO->setCab(cabDummy.load());
        driver->setTexi(cabO);
        sleep(1);
        tcpClient.sendData("we got the cab!");

    } else if(stCarType.at(0) = '0') {
        //set the driver's cab
        sleep(1);
        tcpClient.sendData("getting cab lux");
        tcpClient.reciveData(buffer, sizeof(buffer));
        string stMessCab(buffer, sizeof(buffer));
        LuxuryCab cabDummy;
        cabDummy.setString(stMessCab);
        LuxuryCab* luxuryCabO = new LuxuryCab();
        luxuryCabO->setLuxuryCab(cabDummy.load());
        driver->setTexi(luxuryCabO);
        sleep(1);
        tcpClient.sendData("we got the luxurycab!");
    }

    string stMessage, stMoveBy;
    TripInfo* t= new TripInfo();
    TripInfo tDummy;
    do {
        do {
            //wait for a message to get the trip
            char buffer0[2000];
            tcpClient.reciveData(buffer0, sizeof(buffer0));
            string stMessage(buffer0);
            if (stMessage.compare("start triping shimi") == 0) {
                //tcpClient.sendData("got it");
                char buffer1[40000];
                tcpClient.reciveData(buffer1, sizeof(buffer1));
                string stMessTrip(buffer1, sizeof(buffer1));
                tDummy.setString(stMessTrip);
                t->setTripInfo(tDummy.load());
                driver->setTripInfo(t);
                break;
            }
        } while (stMessage.compare("start triping shimi") != 0);

        do {
            //wait for a message to drive
            char buffer4[1024];
            tcpClient.reciveData(buffer4, sizeof(buffer4));
            string stMoveBy(buffer4);
            if (stMoveBy.compare("you can drive :)") == 0) {
                driver->drive(driver->getTripInfo()->getWay().front());
                sleep(1);
                tcpClient.sendData("drive one step");
            }
            if (stMoveBy.compare("end of trip") == 0) {
                break;
            }
        } while (driver->getTripInfo()->getWay().size() > 0);
        sleep(1);
        tcpClient.sendData("finnish the drive");
        char buffer0[2000];
        tcpClient.reciveData(buffer0, sizeof(buffer0));
        string stMessage(buffer0);
        if (stMessage.compare("go home") == 0){
            break;
        }
    }while (stMessage.compare("go home") != 0);
    tcpClient.~Socket();
    //delete driver;

}