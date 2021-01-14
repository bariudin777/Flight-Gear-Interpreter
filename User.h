//
// Created by ariel on 21/12/18.
//

#ifndef EX3_USER_H
#define EX3_USER_H


#include <unordered_map>
#include <fstream>
#include <iostream>
#include "Command.h"
#include "DefineVarCommand.h"
#include "SymbolTable.h"
#include "ExitCommand.h"
//#include <pthread.h>
//#include <windows.h>
#include <list>

class User {
    unordered_map<string, Command*> m_commands;
    SymbolTable* m_symbolTable;
    unordered_map<string, string> m_namesPaths;
    unordered_map<string, double> m_pathsValues;

    vector<string> m_conditionDetails;
    bool m_isInsideCondition;

    vector<string> analyzeLine(string &line) const;
    void adjustLine(string &line) const;
    void contractVector(vector<string> &vec) const;

    bool isBracketsMatching(const vector<string>& lines) const;

    vector<string> bracketsParser(vector<string>::iterator &itor) const;

public:
    explicit User(SymbolTable* table, vector<pthread_t> *threads);
    ~User();
    vector<string> lexer(string &str);
    void parser(vector<string>& details);

    unordered_map<string,Command*> getMapCommands() const;

    User(pthread_mutex_t * mutex,vector<pthread_t> *threads, ExitCommand *exitCommand);
    void InitializeParameterMap();
};



#endif //EX3_USER_H