//
// Created by daniel on 12/13/18.
//

#ifndef EX3_OPENSERVERCOMMAND_H
#define EX3_OPENSERVERCOMMAND_H


#include "Command.h"
#include "CheckClass.h"
#include "SymbolTable.h"
#include <pthread.h>
#include <list>

class OpenServerCommand : public Command, public CheckClass {



public:

    OpenServerCommand(SymbolTable * symbolTable, vector<pthread_t> *pList);

    int doCommand(vector<string> &text);

    vector<pthread_t> *threads;

    virtual ~OpenServerCommand();

    static SymbolTable * _m_symTable;
};

#endif //EX3_OPENSERVERCOMMAND_H