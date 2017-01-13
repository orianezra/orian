#ifndef EX3_TCP_H
#define EX3_TCP_H
#include "Socket.h"

class Tcp: public Socket {
private:
    int descriptorCommunicateClient;
public:
    /***********************************************************************
    * function name: Tcp												   *
    * The Input: Boolean, true - if server, false if client and port number*
    * The output: none										               *
    * The Function operation: creating new Tcp						       *
    ***********************************************************************/
    Tcp(bool isServers, int port_num);
    /***********************************************************************
    * function name: ~Tcp												   *
    * The Input: none													   *
    * The output: none										               *
    * The Function operation: default destructor					       *
    ***********************************************************************/
    virtual ~Tcp();
/***********************************************************************
	* function name: initialize											   *
	* The Input: none              										   *
	* The output: int number representing the return status		           *
	* The Function operation: initialize the Socket object and getting a   *
	* socket descriptor.												   *
	***********************************************************************/
    int initialize();
    /***********************************************************************
    * function name: sendData											   *
    * The Input: string representing the data to send		               *
    * The output: int number representing the return status		           *
    * The Function operation: sending the input data to the socket         *
    * who connect to this socket. 										   *
    ***********************************************************************/
    int sendData(string data);
    /***********************************************************************
    * function name: recive	`											   *
    * The Input: none										               *
    * The output: int number representing the return status	               *
    * The Function operation: getting data from the other socket and print *
    * the data															   *
    ***********************************************************************/
    int reciveData(char* buffer, int size);
    int accept();
};
#endif //EX3_TCP_H