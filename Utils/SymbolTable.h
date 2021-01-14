//
// Created by ariel on 21/12/18.
//

#ifndef EX3_SYMBOLTABLE_H
#define EX3_SYMBOLTABLE_H


#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class SymbolTable {
    int socketfd;
    unordered_map<string, string> m_namesPaths;      // var to path
    unordered_map<string, double> m_pathsValues;     // paths to values
    pthread_mutex_t * mutex;
public:
    SymbolTable(unordered_map<string, string> &namesPaths, unordered_map<string, double> &pathsValues, pthread_mutex_t * mutex);

    ~SymbolTable();

    void setVarValue(const string &nameVar, double value);

    void setVarPath(const string &nameVar, const string &path);

    void setSocketfd(int socketfd);

    double getVarValue(const string &nameVar) const;

    const string getVarPath(const string &nameVar) const;

    bool isVarExist(const string &nameVar) const;

    void updateMap(vector<string> vals);
};

#endif //EX3_SYMBOLTABLE_H
