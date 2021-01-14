//
// Created by daniel on 12/16/18.
//

#include <iostream>
#include "ConditionParser.h"


ConditionParser::ConditionParser(SymbolTable *table, User* user) {
    this->_symbolTable = table;
    this->user=user;
}


int ConditionParser::doCommand(vector<string> &vec_line) {


    string leftSide;
    string condition;
    string rightSide;
    unsigned long conditionSize;

    //get the condition
    condition = getOperator(vec_line);
    conditionSize = condition.length();

    leftSide = splitWithStringDelimiter(vec_line.at(0), condition);
    rightSide = vec_line.at(0).substr(vec_line.at(0).find(condition)+conditionSize);
    return checkCondition(leftSide, condition, rightSide);

}


bool ConditionParser::checkCondition(string &leftSide, string &operatorStr, string &rightSide) {
    try {
        vector<string> leftVec = user->lexer(leftSide);
        vector<string> rightVec = user->lexer(rightSide);
        leftVec.pop_back();
        rightVec.pop_back();
        double rightVal = ShuntingYard(_symbolTable).calculateExpression(rightVec);
        double leftVal = ShuntingYard(_symbolTable).calculateExpression(leftVec);
        if (operatorStr == "==" || operatorStr == " ==" || operatorStr == "== " || operatorStr == " == ") {
            return rightVal == leftVal;
        } else if (operatorStr == "!=" || operatorStr == " !=" || operatorStr == "!= " || operatorStr == " != ") {
            return rightVal != leftVal;
        } else if (operatorStr == "<" || operatorStr == " <" || operatorStr == "< " || operatorStr == " < ") {
            return leftVal < rightVal;
        } else if (operatorStr == ">" || operatorStr == " >" || operatorStr == "> " || operatorStr == " > ") {
            return leftVal > rightVal;
        } else if (operatorStr == ">=" || operatorStr == " >=" || operatorStr == ">= " || operatorStr == " >= ") {
            return leftVal >= rightVal;
        } else if (operatorStr == "<=" || operatorStr == " <=" || operatorStr == "<= " || operatorStr == " <= ") {
            return leftVal <= rightVal;
        } else {

            throw invalid_argument(operatorStr);
        }

    } catch (invalid_argument noMatch) {
        cout << " No such operator - " << noMatch.what() << endl;
    }

}

ConditionParser::ConditionParser() {}

const vector<string> ConditionParser::createCommandVec(vector<string>::iterator &itor) {
    vector<string> v;
    v.emplace_back(itor->substr(0, itor->find(' ')));
    v.emplace_back(itor->substr(itor->find(' ') + 1));
    itor++;

    while (*itor != "}") {
        v.emplace_back(*itor);
        itor++;
    }
    return v;
}

int ConditionParser::executeCommands(vector<string> commandInfo) {
    //do nothing
    for (auto itor = commandInfo.begin() + 1; itor != commandInfo.end(); itor++) {
        string currStr = *itor;
        if (currStr == "\n" || currStr == "{") {
            continue;
        }
        if (currStr == "}") {
            return 0;
        }
        string nameCommand = currStr.substr(0, currStr.find((' ')));
        if (nameCommand == "while" || nameCommand == "if") {
            vector<string> vec = this->createCommandVec(itor);
            user->parser(vec);
        } else {
            vector<string> toParse = user->lexer(currStr);
            user->parser(toParse);
        }
    }
}

ConditionParser::~ConditionParser() {}
