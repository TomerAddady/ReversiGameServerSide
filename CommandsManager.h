//
// Created by tomer on 24/12/17.
//

#ifndef SERVER_COMMANDSMANAGER_H
#define SERVER_COMMANDSMANAGER_H

#include <map>
#include "Command.h"
using namespace std;

class CommandsManager {
    public:
    CommandsManager();
    ~CommandsManager();
    void executeCommand(string command, vector<string> args);
    private:
    map<string, Command*> commandsMap;
};


#endif //SERVER_COMMANDSMANAGER_H
