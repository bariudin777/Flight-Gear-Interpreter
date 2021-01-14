//
// Created by daniel on 12/20/18.
//

#ifndef PROJECT_DATAREADERSERVER_H
#define PROJECT_DATAREADERSERVER_H

#include <unordered_map>
#include "Utils/CheckClass.h"
#include "Utils/SymbolTable.h"

using namespace std;

class DataReaderServer : public CheckClass {

private:
    int _portNumber;
    int _samplingNumber;
    //unordered_map<string, string> m_namesPaths;
    //unordered_map<string, double> m_pathsValues;
    SymbolTable *_table;
    //void InitializeParameterMap();
    SymbolTable *m_table;


public:
    DataReaderServer(int portNumber, int samplingNumber, SymbolTable * symbolTable);

    SymbolTable *getSymbolTable();

    void Open();

    virtual ~DataReaderServer();

    void updateMap(vector<string> vector);


};


#endif //PROJECT_DATAREADERSERVER_H
