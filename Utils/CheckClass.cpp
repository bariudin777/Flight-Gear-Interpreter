//
// Created by daniel on 12/20/18.
//-


#include <regex>
#include <iostream>
#include "CheckClass.h"


bool CheckClass::isNumber(const string &str) {

    return !str.empty() &&
           (str.find_first_not_of("[0123456789]") == string::npos);
}

vector<string> CheckClass::split(const string &str, char delimiter) {
    auto i = 0;
    vector<string> vec;

    auto pos = str.find(delimiter);

    while (pos != string::npos) {
        vec.push_back(str.substr(i, pos - i));
        i = ++pos;
        pos = str.find(delimiter, pos);
    }

    vec.push_back(str.substr(i, str.length()));

    return vec;
}

bool CheckClass::checkIpAddress(string s) {
    // split the string into tokens
    vector<string> list = split(s, '.');

    // if token size is not equal to four
    if (list.size() != 4)
        return false;

    // validate each token
    for (string str : list) {
        // verify that string is number or not and the numbers
        // are in the valid range
        if (!isNumber(str) || stoi(str) > 255 || stoi(str) < 0)
            return false;

    }
    return true;
}

bool CheckClass::portNumberIsValid(const string &portNumber) {
    regex ex("^([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$");
    if (!regex_match(portNumber, ex))
        throw invalid_argument("Not a valid port number");
    return true;
}

string CheckClass::getOperator(vector<string> &line) {

    regex ex("(<=|>=|!=|==|>|<)");
    string res;
    smatch match;
    try {
        if (regex_search(line.at(0), match, ex) && match.size() > 0) {
            res = match.str(0);
        } else {
            res = string("");

        }
        return res;
    } catch (regex_error &e) {
        cout << e.what() << endl;
        throw e.what();
    }

}

string CheckClass::splitWithStringDelimiter(string &line, string &delimiter) {

    string toReturn;
    toReturn = line.substr(0, line.find(delimiter));
    return toReturn;


}