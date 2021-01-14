//
// Created by ariel on 14/12/18.
//

#include "ShuntingYard.h"
#include "Plus.h"
#include "Minus.h"
#include "Mult.h"
#include "Div.h"
#include "Neg.h"
#include "Number.h"
#include <algorithm>

/**
 * Default Constructor
 */
ShuntingYard::ShuntingYard() : ShuntingYard(nullptr) {}

/**
 * Constructor
 * @param vars_values - an unordered map that maps variables names to their values
 */
ShuntingYard::ShuntingYard(SymbolTable *table) {
    m_table = table;
    m_operatorsTable["+"] = 1;
    m_operatorsTable["-"] = 1;
    m_operatorsTable["*"] = 2;
    m_operatorsTable["/"] = 2;
    m_operatorsTable["("] = -1;
    m_operatorsTable["&"] = 3;
    m_isQueueReversed = false;
}

/**
 * Destructor
 */
ShuntingYard::~ShuntingYard() = default;

/**
 * Splitting each given string to its different segments in sequence - numbers, variables, operators
 * @param str - the string to split
 * @return vector of strings, where each string is a component of the input string
 */
vector<string> ShuntingYard::splitString(string &str) const {
    vector<string> splits;
    string segment;
    string currChar;
    for (unsigned int i = 0; i < str.length(); i++) {
        segment = "";
        currChar = str.substr(i, 1);
        // If the current segment is a number or a name of a variable
        while (currChar != ")" && currChar != "(" && !this->isTokenOperator(currChar)) {
            segment += currChar;
            i++;
            if (i > str.length()) {
                break;
            }
            currChar = str.substr(i, 1);
        }
        // If the segment wasn't a number or variable
        if (segment.empty()) {
            splits.emplace_back(currChar);
        } else {
            splits.emplace_back(segment);
            i--;            // Fixing position of 'i' due to the 'while' loop terminating
        }
    }
    return splits;
}

/**
 * Breaking down each string in a given vector to its different characters - each characters is added to the result
 * @param expressions - vector of strings, where each string is (part of) a mathematical expression,
 * including parenthesis, without white spaces.
 * @return vector of strings, where each string is a single character
 */
vector<string> ShuntingYard::deconstruct(vector<string> &expressions) const {
    vector<string> components;

    for (auto &str : expressions) {
        if (this->isTokenNumber(str) || this->isTokenOperator(str) || str == "(" || str == ")") {
            components.emplace_back(str);

            // Add the variable's value instead of its name
        } else if (m_table != nullptr && this->isTokenVariable(str)) {
            components.emplace_back(to_string(m_table->getVarValue(str)));

            // If the string is a complex expression consisting of numbers, variables and operators
        } else {
            // If the current string is '123+x/y', split it into its different segments - {123,+,x,/,y}.
            vector<string> splits = this->splitString(str);
            /*
             * Next, in case the string had variables names, convert them into their values by applying this
             * function on the splits.
             */
            vector<string> appliedSplits = this->deconstruct(splits);
            // Add the final applied splits to the components vector
            components.insert(components.end(), appliedSplits.begin(), appliedSplits.end());
        }
    }
    this->fixNegatives(components);
    return components;
}

void ShuntingYard::fixNegatives(vector<string> &components) const {
    // Changing a minus without a preceding number to a negative operator symbol
    for (unsigned int i = 0; i < components.size(); i++) {
        if (components.at(i) == "-") {
            if (i == 0) {
                components.at(0) = "&";
            } else if (!this->isTokenNumber(components.at(i - 1))) {
                components.at(i) = "&";
            }
        }
    }
    // Removing pairs of consecutive 'minus' signs and replacing with 'plus' sign
    vector<string> temp = components;
    auto itor = temp.begin();
    for (unsigned int i = 1; i < components.size(); i++, itor++) {
        if (components.at(i) == "&" && components.at(i - 1) == "&") {
            itor = temp.erase(itor - 1, itor + 1);
            itor = temp.insert(itor, "+");
        }
    }
}

/**
 * Determining which string represents high-precedence mathematical operator by subtracting the operators values
 * according to a map
 * @param currOper - current operator to check
 * @param topStackOper - operator at the top of the stack
 * @return 1 if 'curr' has higher precedence, 0 if equal and -1 if 'curr' has lower
 */
int ShuntingYard::getPrecedence(const string &currOper, const string &topStackOper) const {
    return m_operatorsTable.at(currOper) - m_operatorsTable.at(topStackOper);
}

/**
 * Executing the Shunting-Yard Algorithm
 * @param expressions - vector of strings, where each string is a (part of) a mathematical expression,
 * including parenthesis, without white spaces.
 * @return a queue of numbers of operators based on the shunting-yard algorithm
 */
queue<string> ShuntingYard::getQueue(vector<string> &expressions) {
    // Simplifying the expressions into different strings where each string is either a number or an operator
    vector<string> components = this->deconstruct(expressions);
    stack<string> operators;
    queue<string> numbers;

    // Getting all the expressions to the queue in correct order
    for (string &str : components) {
        if (this->isTokenNumber(str)) {
            numbers.push(str);
        } else if (this->isTokenOperator(str)) {
            // Moving bigger-precedence-operators from the stack to the queue
            while (!operators.empty() && this->getPrecedence(str, operators.top()) <= 0) {
                numbers.push(operators.top());
                operators.pop();
            }
            // Finally add the current operator to the stack
            operators.push(str);
        } else if (str == "(") {
            operators.push(str);
        } else {        // 'str' is ')'
            // Moving all the operators to the queue until the top is '(' and remove it
            while (!operators.empty()) {
                string temp = operators.top();
                if (temp == "(") {
                    operators.pop();
                    break;
                }
                numbers.push(temp);
                operators.pop();
            }
        }
    }
    // Moving any remaining operators from the stack to the queue
    while (!operators.empty()) {
        numbers.push(operators.top());
        operators.pop();
    }
    return numbers;
}

/**
 * Checking whether a given string input is a simple math binary operator - +,-,*,/
 * @param str - string to determine if it's a math operator
 * @return true if the string is an operator, false otherwise
 */
bool ShuntingYard::isTokenOperator(const string &str) const {
    if (str.length() > 1) {
        return false;
    }
    return (str == "+") || (str == "-") || (str == "*") || (str == "/") || (str == "&");
}

/**
 * Checking whether a given string input represents a number
 * @param str - string to determine if it's a number
 * @return true if the string is a number, false otherwise
 */
bool ShuntingYard::isTokenNumber(const string &str) const {
    // Try to convert the string to a number
    try {
        //float x = stof(str);
        double x = stod(str);

//        // If the lengths are equal than the conversion didn't cut any characters, meaning the string is a number
        return true;
        // If the conversion threw exception then the string wasn't a number
    } catch (...) {
        return false;
    }
}

/**
 * Checking whether a given string input is a variable from the variables map
 * @param str - string to determine if it's a variable
 * @return true if the string is a variable, false otherwise
 */
bool ShuntingYard::isTokenVariable(const string &str) const {
    return m_table->isVarExist(str);
}

/**
 * Reversing a given queue
 * @param q - queue of strings - outcome of the algorithm
 * @return the input queue - reversed
 */
queue<string> &ShuntingYard::reverseQueue(queue<string> &q) {
    stack<string> s;
    while (!q.empty()) {
        s.push(q.front());
        q.pop();
    }
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
    return q;
}

/**
 * Converting the expression represented by the input queue to an actual expression object
 * @param q - queue of strings - outcome of the algorithm
 * @param exps - vector of pointers to expressions
 * @return corresponding expression-pointer object
 */

Expression *ShuntingYard::generateExpression(queue<string> &q, vector<Expression *> &exps) {
    // Reversing the queue to analyze the characters from the back to the front
    if (!m_isQueueReversed) {
        q = this->reverseQueue(q);
        m_isQueueReversed = true;
    }
    if (q.empty()) {
        Expression *e = new Number(0);
        exps.emplace_back(e);
        return e;
    }
    if (this->isTokenNumber(q.front())) {
        float num = stof(q.front());
        q.pop();
        Expression *e = new Number(num);
        exps.emplace_back(e);
        return e;
    }
    // The front is an operator
    char c = q.front()[0];
    q.pop();
    Expression *e;
    switch (c) {
        // Recursively calling this function to assign the members of the expression
        case ('+'):
            e = new Plus(this->generateExpression(q, exps), this->generateExpression(q, exps));
            break;
        case ('-'):
            e = new Minus(this->generateExpression(q, exps), this->generateExpression(q, exps));
            break;
        case ('*'):
            e = new Mult(this->generateExpression(q, exps), this->generateExpression(q, exps));
            break;
        case ('/'):
            e = new Div(this->generateExpression(q, exps), this->generateExpression(q, exps));
            break;
        default:
            e = new Neg(this->generateExpression(q, exps));
            break;
    }
    exps.emplace_back(e);
    return e;
}

/**
 * Commencing the algorithm and calculating a given expression
 * @param expressions - vector of strings, where each string is a (part of) a mathematical expression,
 * including parenthesis, without white spaces.
 * @return expression's value
 */
double ShuntingYard::calculateExpression(vector<string> &expressions) {
    queue<string> q = this->getQueue(expressions);
    vector<Expression *> v;
    double result = this->generateExpression(q, v)->calculate();
    for (Expression *&ptr : v) {
        delete ptr;
    }
    return result;
}
