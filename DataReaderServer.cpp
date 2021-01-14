//
// Created by daniel on 12/20/18.
//
#include "Utils/SymbolTable.h"
#include <sys/socket.h>
#include <cstdio>
#include <cstdlib>
#include <netinet/in.h>
#include <strings.h>
#include "DataReaderServer.h"
#include <iostream>
#include <unistd.h>
#include <cstring>

using namespace std;

#define MAX_BUFFER_SIZE 256

DataReaderServer::DataReaderServer(int portNumber, int samplingNumber, SymbolTable * symbolTable) {
    this->_portNumber = portNumber;
    this->_samplingNumber = samplingNumber;
    //InitializeParameterMap();
    _table = symbolTable; // new SymbolTable(m_namesPaths, m_pathsValues);
}


void DataReaderServer::Open() {

    int sockfd, newsockfd, clilen;
    char buffer[MAX_BUFFER_SIZE + 1];
    char doubleBuffer[2 * MAX_BUFFER_SIZE + 1];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
/* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
/* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(this->_portNumber);
/* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
/* Now start listening for the clients, here process will
   * go in sleep mode and will wait for the incoming connection
*/
    listen(sockfd, 5);//TODO change to vec(1)
    clilen = sizeof(cli_addr);
/* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

//start reading messages from simulator and update the map accordingly

    bzero(buffer, MAX_BUFFER_SIZE + 1);

    vector<string> stringVals;
    string remain;
    int index;
    bool flag = true;
    while (read(newsockfd, buffer, MAX_BUFFER_SIZE) > 0) {
        if(flag){
            cout << "start reading messages from simulator and update the map accordingly" << endl;
            flag = false;
        }
        strcpy(doubleBuffer, remain.c_str());
        strcat(doubleBuffer, buffer);
        const char *ptr = strchr(doubleBuffer, '\n');
        if (ptr) {
            int index = ptr - doubleBuffer;
            string bufferString(doubleBuffer);
            string line(doubleBuffer, index);
            stringVals = split(line, ',');
            updateMap(stringVals);
            remain = bufferString.substr(index + 1);
        }
        bzero(buffer, MAX_BUFFER_SIZE + 1);
        stringVals = {};
    }
}

//void DataReaderServer::InitializeParameterMap() {
//    m_namesPaths["airspeed"] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
//    m_namesPaths["altimeter_altitude"] = "/instrumentation/altimeter/indicated-altitude-ft";
//    m_namesPaths["altimeter_pressure"] = "/instrumentation/altimeter/pressure-alt-ft";
//    m_namesPaths["attiude_indicated-pitch"] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
//    m_namesPaths["attiude_indicated-roll"] = "/instrumentation/attitude-indicator/indicated-roll-deg";
//    m_namesPaths["attiude_internal-pitch"] = "/instrumentation/attitude-indicator/internal-pitch-deg";
//    m_namesPaths["attiude_internal-roll"] = "/instrumentation/attitude-indicator/internal-roll-deg";
//    m_namesPaths["encoder_indicated-altitude"] = "/instrumentation/encoder/indicated-altitude-ft";
//    m_namesPaths["encoder_pressure"] = "/instrumentation/encoder/pressure-alt-ft";
//    m_namesPaths["gps_indicated-altitude"] = "/instrumentation/gps/indicated-altitude-ft";
//    m_namesPaths["gps_indicated-ground-speed"] = "/instrumentation/gps/indicated-ground-speed-kt";
//    m_namesPaths["gps_indicated-vertical-speed"] = "/instrumentation/gps/indicated-vertical-speed";
//    m_namesPaths["heading"] = "/instrumentation/heading-indicator/indicated-heading-deg";
//    m_namesPaths["compass"] = "/instrumentation/magnetic-compass/indicated-heading-deg";
//    m_namesPaths["slip-skid-ball"] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
//    m_namesPaths["turn_rate"] = "/instrumentation/turn-indicator/indicated-turn-rate";
//    m_namesPaths["vertical_speed_indicator"] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
//    m_namesPaths["aileron"] = "/controls/flight/aileron";
//    m_namesPaths["elevator"] = "/controls/flight/elevator";
//    m_namesPaths["rudder"] = "/controls/flight/rudder";
//    m_namesPaths["flaps"] = "/controls/flight/flaps";
//    m_namesPaths["throttle"] = "/controls/engines/engine/throttle";
//    m_namesPaths["rpm"] = "/engines/engine/rpm";
//    m_pathsValues.insert(pair<string, double>("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/altimeter/indicated-altitude-ft", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/altimeter/pressure-alt-ft", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/attitude-indicator/indicated-roll-deg", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/attitude-indicator/internal-pitch-deg", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/attitude-indicator/internal-roll-deg", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/encoder/indicated-altitude-ft", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/encoder/pressure-alt-ft", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/gps/indicated-altitude-ft", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/gps/indicated-ground-speed-kt", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/gps/indicated-vertical-speed", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/heading-indicator/indicated-heading-deg", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/magnetic-compass/indicated-heading-deg", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/slip-skid-ball/indicated-slip-skid", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/turn-indicator/indicated-turn-rate", 0));
//    m_pathsValues.insert(pair<string, double>("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0));
//    m_pathsValues.insert(pair<string, double>("/controls/flight/aileron", 0));
//    m_pathsValues.insert(pair<string, double>("/controls/flight/elevator", 0));
//    m_pathsValues.insert(pair<string, double>("/controls/flight/rudder", 0));
//    m_pathsValues.insert(pair<string, double>("/controls/flight/flaps", 0));
//    m_pathsValues.insert(pair<string, double>("/controls/engines/engine/throttle", 0));
//    m_pathsValues.insert(pair<string, double>("/engines/engine/rpm", 0));
//}

void DataReaderServer::updateMap(vector<string> vals) {
    _table->updateMap(vals);
}

SymbolTable *DataReaderServer::getSymbolTable() {
    return _table;
}

DataReaderServer::~DataReaderServer() {
    delete _table;
}
