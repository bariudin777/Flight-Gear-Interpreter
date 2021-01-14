//
// Created by ariel on 21/12/18.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include <string>
#include <vector>

using namespace std;

class Command {

public:
    virtual int doCommand(vector<string> &commandInfo) = 0;
};

#endif //EX3_COMMAND_H
