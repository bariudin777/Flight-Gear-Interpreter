//
// Created by daniel on 12/22/18.
//

#include "IfCommand.h"

IfCommand::IfCommand(SymbolTable *table) {
    this->_table = table;
}

int IfCommand::doCommand(vector<string> &text) {
    unordered_map<string, Command *> commandMap;
    commandMap = _user->getMapCommands();

    if (toParse->doCommand(text)) {
        this->executeCommands(text);
    }
    return 0;
}

IfCommand::~IfCommand() {}
