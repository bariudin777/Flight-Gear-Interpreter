//
// Created by daniel on 12/22/18.
//

#ifndef PROJECT_IFCOMMAND_H
#define PROJECT_IFCOMMAND_H


#include "ConditionParser.h"
#include "User.h"
#include "LoopCommand.h"


class IfCommand : public ConditionParser {
    SymbolTable *_table;
    ConditionParser *toParse;
    User *_user;

public:
    IfCommand(SymbolTable *table);
    virtual int doCommand(vector<string> &text);

    virtual ~IfCommand();
};


#endif //PROJECT_IFCOMMAND_H
