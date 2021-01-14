//
// Created by ariel on 21/12/18.
//

#ifndef EX3_DEFINEVARCOMMAND_H
#define EX3_DEFINEVARCOMMAND_H


#include <unordered_map>
#include "Command.h"
#include "SymbolTable.h"

class DefineVarCommand : public Command {
    SymbolTable *m_symTable;

private:
    bool isBoundedToVar(const vector<string> &commandInfo) const;

public:
    explicit DefineVarCommand(SymbolTable *&table);

    virtual ~DefineVarCommand();

    virtual int doCommand(vector<string> &commandInfo);
};


#endif //EX3_DEFINEVARCOMMAND_H
