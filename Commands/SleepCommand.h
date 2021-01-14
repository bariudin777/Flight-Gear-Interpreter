//
// Created by daniel on 12/22/18.
//

#ifndef PROJECT_SLEEPCOMMAND_H
#define PROJECT_SLEEPCOMMAND_H


#include "Command.h"

class SleepCommand : public Command {

public:
    int doCommand(vector<string> &commandInfo) override;

     virtual ~SleepCommand();
};


#endif //PROJECT_SLEEPCOMMAND_H
