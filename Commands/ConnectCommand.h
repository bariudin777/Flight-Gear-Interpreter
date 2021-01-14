//
// Created by daniel on 12/15/18.
//

#ifndef EX3_CONNECTCOMMAND_H
#define EX3_CONNECTCOMMAND_H


#include "Command.h"
#include "CheckClass.h"
#include "SymbolTable.h"

class ConnectCommand : public Command, public CheckClass {
    SymbolTable *_m_symTable;

public:
    ConnectCommand(SymbolTable * symbolTable);

    int doCommand(vector<string> &vec);

    virtual ~ConnectCommand();
};


#endif //EX3_CONNECTCOMMAND_H
