//
// Created by daniel on 12/26/18.
//

#include "ExitCommand.h"

int ExitCommand::doCommand(vector<string> &commandInfo) {
    exitOccured = true;
}

ExitCommand::~ExitCommand() {

}

ExitCommand::ExitCommand(){
    exitOccured = false;
}

bool ExitCommand::isExitOccured() const {
    return exitOccured;
}
