//
// Created by daniel on 12/27/18.
//

#include "RunCommand.h"

RunCommand::~RunCommand() {

}

RunCommand::RunCommand(User * user) {
    this->user = user;
}


int RunCommand::doCommand(vector<string> &commandInfo) {
    string temp = commandInfo.at(0).c_str();
    string address = temp.substr(1,temp.length()-2);
    vector<string> toParse = user->lexer(address);
    user->parser(toParse);
    return 0;
}
