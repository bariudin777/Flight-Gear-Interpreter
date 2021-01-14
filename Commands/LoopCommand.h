//
// Created by daniel on 12/22/18.
//

#ifndef PROJECT_LOOPCOMMAND_H
#define PROJECT_LOOPCOMMAND_H


#include "ConditionParser.h"
#include "SymbolTable.h"
#include "User.h"

class LoopCommand : public ConditionParser {

public:
    LoopCommand(SymbolTable *table, User* user);
    int doCommand(vector<string> &text);

    virtual ~LoopCommand();

};


#endif //PROJECT_LOOPCOMMAND_H
