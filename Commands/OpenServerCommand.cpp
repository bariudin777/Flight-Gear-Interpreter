//
// Created by daniel on 12/13/18.
//

#include <stdexcept>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <netdb.h>
#include <stdexcept>
#include <iostream>
#include "OpenServerCommand.h"
#include "DataReaderServer.h"
#include <pthread.h>
SymbolTable * OpenServerCommand::_m_symTable;

struct DataServerParams{
    int portNum;
    int sampelingCount;
};

void * openDataServerReader(void *arg){
    DataServerParams* dataServerParams = (struct DataServerParams *)arg;
    DataReaderServer* dataReaderServer = new DataReaderServer(dataServerParams->portNum,dataServerParams->sampelingCount, OpenServerCommand::_m_symTable);
//    OpenServerCommand::_m_symTable = dataReaderServer->getSymbolTable();
    dataReaderServer->Open();
}


int OpenServerCommand::doCommand(vector<string> &text) {

    try {
        if(text.size() != 2){
            throw invalid_argument("Invalid number of arguments for OpenServerCommand");
        }
        if (!portNumberIsValid(text.at(0))) {
            throw invalid_argument("Port number is invalid");
        }
        if(!(isNumber(text.at(1)) && stoi(text.at(1)) > 0))
            throw invalid_argument("Sampling number is invalid ");
    } catch (invalid_argument e) {
        cout <<  e.what()  << endl;
        exit(0);
    }
    int portNumber, samplingNumber;
    portNumber = stoi(text.at(0));
    samplingNumber = stoi(text.at(1));
    DataServerParams * dataServerParams = new DataServerParams();
    dataServerParams->portNum = portNumber;
    dataServerParams->sampelingCount = samplingNumber;
    pthread_t thread;
    pthread_create(&thread, nullptr, openDataServerReader ,dataServerParams);
    pthread_detach(thread);
    threads->push_back(thread);
}

OpenServerCommand::OpenServerCommand(SymbolTable * symbolTable, vector<pthread_t> *pList) {
    this->_m_symTable = symbolTable;
    this->threads = pList;
}

OpenServerCommand::~OpenServerCommand() {}

