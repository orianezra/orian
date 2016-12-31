//
// Created by orian on 12/30/16.
//

#ifndef EX3_UDP_H
#define EX3_UDP_H

/*
* UDP header file. the class inherit from
* socket. methods of udp socket type
*/



#include "Socket.h"


class Udp: public Socket {
public:
    //The Input: Boolean, true - if server, false if client and port number
    //The Function operation: creating new Udp
    Udp(bool isServers, int port_num);
    // The Function operation: default destructor
    virtual ~Udp();
    // The Function operation: initialize the Socket object and getting a
    // socket descriptor.
    int initialize();
    // The Function operation: sending the input data to the socket
    // who connect to this socket.
    int sendData(string data);
    // The Function operation: getting data from the other socket and print
    // the data
    int reciveData(char* buffer, int size);
};

#endif /* UDP_H_ */

