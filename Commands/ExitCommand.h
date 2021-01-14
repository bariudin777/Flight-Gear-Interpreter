//
// Created by daniel on 12/26/18.
//

#ifndef PROJECT_EXITCOMMAND_H
#define PROJECT_EXITCOMMAND_H


#include "Command.h"

class ExitCommand : public Command {
    bool exitOccured;
public:

    int doCommand(vector<string> &commandInfo) override;

    virtual ~ExitCommand();

    ExitCommand();

    bool isExitOccured() const;

};


#endif //PROJECT_EXITCOMMAND_H
