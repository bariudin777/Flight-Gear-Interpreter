//
// Created by daniel on 12/16/18.
//

#ifndef EX3_CONDITIONPARSER_H
#define EX3_CONDITIONPARSER_H


#include "Command.h"
#include "ShuntingYard.h"
#include "DefineVarCommand.h"
#include "User.h"
#include "CheckClass.h"
#include <unordered_map>

class ConditionParser : public Command, CheckClass {
protected:
    User *user;
    SymbolTable *_symbolTable;

protected:
    const vector<string> createCommandVec(vector<string>::iterator &itor);
    int executeCommands(vector<string> commandInfo);

public:

    ConditionParser(SymbolTable *table, User* user);

    ConditionParser();

    int doCommand(vector<string> &line);

    bool checkCondition(string &var, string &operatorStr, string &rightExp);

    virtual ~ConditionParser();

};


#endif //EX3_CONDITIONPARSER_H
