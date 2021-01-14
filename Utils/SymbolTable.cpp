//
// Created by ariel on 20/12/18.
//

#include <cstring>
#include <unistd.h>
#include "SymbolTable.h"



SymbolTable::SymbolTable(unordered_map<string, string> &namesPaths, unordered_map<string, double> &pathsValues, pthread_mutex_t * mutex) {
    m_namesPaths = namesPaths;
    m_pathsValues = pathsValues;
    this->mutex = mutex;
}

SymbolTable::~SymbolTable() = default;

void SymbolTable::setSocketfd(int socketfd) {
    this->socketfd = socketfd;
}

void SymbolTable::setVarValue(const string &nameVar, double value) {
    pthread_mutex_lock(this->mutex);
    if (m_namesPaths.count(nameVar) == 0) {// not a bounded variable
        m_pathsValues[nameVar] = value;
    } else {
        m_pathsValues[m_namesPaths.at(nameVar)] = value;
        char toWrite[500] = "set ";
        strcat(toWrite, m_namesPaths.at(nameVar).c_str());
        strcat(toWrite, " ");
        strcat(toWrite, to_string(value).c_str());
        strcat(toWrite, "\r\n");
        int n = write(this->socketfd, toWrite, strlen(toWrite));
        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
    }
    pthread_mutex_unlock(this->mutex);
}

void SymbolTable::setVarPath(const string &nameVar, const string &path) {
    pthread_mutex_lock(this->mutex);
    m_namesPaths[nameVar] = path;
    if(m_pathsValues.count(path) == 0)//in case the path wasn't in the original xml.
        m_pathsValues[path] = 0;
    pthread_mutex_unlock(this->mutex);
}

double SymbolTable::getVarValue(const string &nameVar) const {
    double value;
    pthread_mutex_lock(this->mutex);
    if (m_namesPaths.count(nameVar) == 0)//unbounded variable
        value = m_pathsValues.at(nameVar);
    else
        value = m_pathsValues.at(m_namesPaths.at(nameVar));
    pthread_mutex_unlock(this->mutex);
    return value;
}

const string SymbolTable::getVarPath(const string &nameVar) const {
    pthread_mutex_lock(this->mutex);
    string returnValue = m_namesPaths.at(nameVar);
    pthread_mutex_unlock(this->mutex);
    return returnValue;
}

bool SymbolTable::isVarExist(const string &nameVar) const {
    pthread_mutex_lock(this->mutex);
    bool returnValue = m_namesPaths.count(nameVar) == 1 || m_pathsValues.count(nameVar) == 1;
    pthread_mutex_unlock(this->mutex);
    return returnValue;
}

void SymbolTable::updateMap(vector<string> vals) {
    pthread_mutex_lock(this->mutex);
    m_pathsValues.at("/instrumentation/airspeed-indicator/indicated-speed-kt") = stod(vals.at(0));
    m_pathsValues.at("/instrumentation/altimeter/indicated-altitude-ft") = stod(vals.at(1));
    m_pathsValues.at("/instrumentation/altimeter/pressure-alt-ft") = stod(vals.at(2));
    m_pathsValues.at("/instrumentation/attitude-indicator/indicated-pitch-deg") = stod(vals.at(3));
    m_pathsValues.at("/instrumentation/attitude-indicator/indicated-roll-deg") = stod(vals.at(4));
    m_pathsValues.at("/instrumentation/attitude-indicator/internal-pitch-deg") = stod(vals.at(5));
    m_pathsValues.at("/instrumentation/attitude-indicator/internal-roll-deg") = stod(vals.at(6));
    m_pathsValues.at("/instrumentation/encoder/indicated-altitude-ft") = stod(vals.at(7));
    m_pathsValues.at("/instrumentation/encoder/pressure-alt-ft") = stod(vals.at(8));
    m_pathsValues.at("/instrumentation/gps/indicated-altitude-ft") = stod(vals.at(9));
    m_pathsValues.at("/instrumentation/gps/indicated-ground-speed-kt") = stod(vals.at(10));
    m_pathsValues.at("/instrumentation/gps/indicated-vertical-speed") = stod(vals.at(11));
    m_pathsValues.at("/instrumentation/heading-indicator/indicated-heading-deg") = stod(vals.at(12));
    m_pathsValues.at("/instrumentation/magnetic-compass/indicated-heading-deg") = stod(vals.at(13));
    m_pathsValues.at("/instrumentation/slip-skid-ball/indicated-slip-skid") = stod(vals.at(14));
    m_pathsValues.at("/instrumentation/turn-indicator/indicated-turn-rate") = stod(vals.at(15));
    m_pathsValues.at("/instrumentation/vertical-speed-indicator/indicated-speed-fpm") = stod(vals.at(16));
    m_pathsValues.at("/controls/flight/aileron") = stod(vals.at(17));
    m_pathsValues.at("/controls/flight/elevator") = stod(vals.at(18));
    m_pathsValues.at("/controls/flight/rudder") = stod(vals.at(19));
    m_pathsValues.at("/controls/flight/flaps") = stod(vals.at(20));
    m_pathsValues.at("/controls/engines/current-engine/throttle") = stod(vals.at(21));
    m_pathsValues.at("/engines/engine/rpm") = stod(vals.at(22));
    pthread_mutex_unlock(this->mutex);
}