//
// Created by daniel on 12/26/18.
//

#ifndef PROJECT_ENTERCCOMMAND_H
#define PROJECT_ENTERCCOMMAND_H


#include "Command.h"

class EntercCommand : public Command {
public:
    int doCommand(vector<string> &commandInfo) override;

    virtual ~EntercCommand();
};


#endif //PROJECT_ENTERCCOMMAND_H
