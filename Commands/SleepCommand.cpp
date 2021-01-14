//
// Created by daniel on 12/22/18.
//

#include "SleepCommand.h"
#include <unistd.h>

int SleepCommand::doCommand(vector<string> &commandInfo) {
    //calling the thread to sleep for some time( in seconds)
    sleep(stoi(commandInfo.at(0)) / 1000);
}

SleepCommand::~SleepCommand() {}
