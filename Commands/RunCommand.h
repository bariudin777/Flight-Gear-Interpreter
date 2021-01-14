//
// Created by daniel on 12/27/18.
//

#ifndef PROJECT_RUNCOMMAND_H
#define PROJECT_RUNCOMMAND_H


#include "Command.h"
#include "User.h"

class RunCommand : public Command {
    User * user;
public:
    RunCommand(User *pUser);

    int doCommand(vector<string> &commandInfo) override;

    virtual ~RunCommand();

};


#endif //PROJECT_RUNCOMMAND_H
