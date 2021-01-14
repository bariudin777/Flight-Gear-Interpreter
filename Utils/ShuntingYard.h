//
// Created by ariel on 21/12/18.
//

#ifndef EX3_SHUNTINGYARD_H
#define EX3_SHUNTINGYARD_H


#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <unordered_map>
#include "Expression.h"
#include "SymbolTable.h"

using namespace std;

class ShuntingYard {
    SymbolTable* m_table;
    unordered_map<string, int> m_operatorsTable;
    bool m_isQueueReversed;

private:
    // Aid functions
    bool isTokenOperator(const string &str) const;
    bool isTokenNumber(const string &str) const;
    bool isTokenVariable(const string &str) const;
    vector<string> splitString(string &str) const;
    vector<string> deconstruct(vector<string> &expressions) const;
    void fixNegatives(vector<string> &components) const;

    int getPrecedence(const string& currOper, const string& topStackOper) const;

    // Main algorithm function
    queue<string> getQueue(vector<string> &expressions);

    // Used to create the final expression to calculate
    queue<string>& reverseQueue(queue<string>& q);
    Expression* generateExpression(queue<string>& q, vector<Expression*> &exps);

public:
    ShuntingYard();
    explicit ShuntingYard(SymbolTable* table);
    ~ShuntingYard();

    double calculateExpression(vector<string>& expressions);
};

#endif //EX3_SHUNTINGYARD_H
