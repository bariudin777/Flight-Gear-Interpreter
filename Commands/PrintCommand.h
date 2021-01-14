//
// Created by daniel on 12/22/18.
//

#ifndef PROJECT_PRINTCOMMAND_H
#define PROJECT_PRINTCOMMAND_H


#include "Command.h"
#include "CheckClass.h"
#include "SymbolTable.h"


class PrintCommand : public Command, CheckClass {
    SymbolTable *_table;
public:
    int doCommand(vector<string> &commandInfo) override;

    virtual ~PrintCommand();

    PrintCommand(SymbolTable *table);

    string getWord(const string &wordToWorkOn);

    string splitWord(const string &str);

};


#endif //PROJECT_PRINTCOMMAND_H
