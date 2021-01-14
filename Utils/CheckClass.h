//
// Created by daniel on 12/20/18.
//

#ifndef PROJECT_CHECKCLASS_H
#define PROJECT_CHECKCLASS_H

#include <string>
#include <vector>

using namespace std;


class CheckClass {

public:
    bool isNumber(const string &str);

    vector<string> split(const string &s, char delimiter);

    bool checkIpAddress(string s);

    bool portNumberIsValid(const string &portNumber);

    string getOperator(vector<string> &line);

    string splitWithStringDelimiter(string &line, string &delimiter);

};

#endif //PROJECT_CHECKCLASS_H
