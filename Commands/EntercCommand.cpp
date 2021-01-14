//
// Created by daniel on 12/26/18.
//

#include <iostream>
#include "EntercCommand.h"


int EntercCommand::doCommand(vector<string> &commandInfo) {
    cout << "Press Enter to continue" << endl;
    getchar();
    return  0;
}

EntercCommand::~EntercCommand() {

}
