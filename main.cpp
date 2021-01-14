// Created by daniel on 12/19/18.

#include "Commands/ConnectCommand.h"
#include "Utils/SymbolTable.h"
#include "Commands/PrintCommand.h"

using namespace std;

#include "User.h"
#include "Commands/OpenServerCommand.h"
#include "DataReaderServer.h"
#include "Commands/ExitCommand.h"

int main() {

    vector<pthread_t> threads;
    pthread_mutex_t mutex;
    ExitCommand * exitCommand = new ExitCommand();
    User *user = new User(&mutex,&threads,exitCommand);
    while(!exitCommand->isExitOccured()){
        string nextLine;
        getline(cin,nextLine);
        vector<string> toParse = user->lexer(nextLine);
        user->parser(toParse);
    }

    for (auto x : threads) {
        pthread_join(x, NULL);
    }
    pthread_mutex_destroy(&mutex);
    delete exitCommand;
    delete user;
    return 0;
}

