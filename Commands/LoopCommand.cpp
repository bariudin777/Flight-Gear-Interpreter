//
// Created by daniel on 12/22/18.
//

#include "LoopCommand.h"


LoopCommand::LoopCommand(SymbolTable *table, User *user) : ConditionParser(table, user) {

}

int LoopCommand::doCommand(vector<string> &text) {
    unordered_map<string, Command *> commandMap;
    commandMap = this->user->getMapCommands();
    vector<string> temp = text;

    while (ConditionParser::doCommand(temp)) {
        if (text.empty()) {
            text = temp;
        }
        this->executeCommands(text);
    }
}

LoopCommand::~LoopCommand() {}
