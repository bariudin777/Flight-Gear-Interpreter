//
// Created by ariel on 21/12/18.
//

#include "DefineVarCommand.h"
#include "ShuntingYard.h"
#include <algorithm>
#include <iostream>

#define CONTROLS_PATH "/controls"
#define INSTRUMENT_PATH "/instrumentation"


DefineVarCommand::DefineVarCommand(SymbolTable *&table) {
    m_symTable = table;
}

DefineVarCommand::~DefineVarCommand() {}

int DefineVarCommand::doCommand(vector<string> &commandInfo) {
    string nameVar = commandInfo.at(0);

    string arg = commandInfo.back();
    // 1. Check if it's a bind to a path
    if (arg.find(CONTROLS_PATH) < arg.length() || arg.find(INSTRUMENT_PATH) < arg.length()) {
        m_symTable->setVarPath(nameVar, arg);
        return 0;
    }
    // 2. Check if it's equal to a variable
    if (m_symTable->isVarExist(arg)) {
        m_symTable->setVarValue(nameVar, m_symTable->getVarValue(arg));
        // If the new variable is bounded to a known already-bounded variable. If not - don't change its path
        if (this->isBoundedToVar(commandInfo)) {
            m_symTable->setVarPath(nameVar, m_symTable->getVarPath(arg));
        }
        return 0;
    }
    // 3. If it's equal to a number or an expression - calculate the expression and assign it as the value
    vector<string> temp;
    // Adding all the expression components to the vector to be evaluated (index 1 is '=')
    temp.insert(temp.end(), commandInfo.begin() + 2, commandInfo.end());
    try {
        m_symTable->setVarValue(nameVar, ShuntingYard(m_symTable).calculateExpression(temp));
    } catch (invalid_argument &e) {
        cout << e.what() << endl;
        return 1;
    }
    return 0;
}

bool DefineVarCommand::isBoundedToVar(const vector<string> &commandInfo) const {
    for (auto &str : commandInfo) {
        if (str == "bind") {
            return true;
        }
    }
    return false;
}
