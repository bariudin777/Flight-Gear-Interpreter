//
// Created by daniel on 12/15/18.
//

#include <sys/socket.h>
#include <bits/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <stdexcept>
#include <iostream>
#include "ConnectCommand.h"
#include "SymbolTable.h"


ConnectCommand::ConnectCommand(SymbolTable * symbolTable) {
    this->_m_symTable = symbolTable;
}


int ConnectCommand::doCommand(vector<string> &vec) {

    /*
     * Verify that we got 2 parameters.
     * Verify that first parameter is a valid ip address.
     * Verify that second parameter is a valid port number.
     * */

    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    //check if there are 2 parameters
    if (vec.size() < 2) {//Verify that we got 2 parameters
        fprintf(stderr, "usage %s hostname port\n", vec.at(0).c_str());// TODO
        throw invalid_argument("there are not enough parameters ");
    }

    //check if the port number is valid or in use.

    try {
        if (!checkIpAddress(vec.at(0))) {
            throw invalid_argument("IP address is not valid");
        }
        if (!portNumberIsValid(vec.at(1))) {
            throw invalid_argument("Port number is not valid");
        }

    } catch (invalid_argument e) {
        cout << e.what() << endl;
        exit(0);
    }
    portno = atoi(vec.at(1).c_str());
    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(vec.at(0).c_str());//TODO "gethostbyname" is out of order

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }
    this->_m_symTable->setSocketfd(sockfd);
    return sockfd;

}

ConnectCommand::~ConnectCommand() {}





