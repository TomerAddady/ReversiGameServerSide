//
// Created by tomer on 24/12/17.
//

#include "CommandsManager.h"
#include "StartCommand.h"
#include "JoinCommand.h"
#include "GetGamesListCommand.h"
#include "CloseCommand.h"
#include "PlayCommand.h"

CommandsManager::CommandsManager(Server * s) {

    commandsMap["start"] = new StartCommand(s);
    commandsMap["join"] = new JoinCommand(s);
    commandsMap["list_gam"] = new GetGamesListCommand(s);
    commandsMap["close"] = new CloseCommand(s);
    commandsMap["play"] = new PlayCommand();
}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}

void CommandsManager::executeCommand(string command, vector<string> args) {
    Command *commandObj = commandsMap[command];
    commandObj ->execute(args);
}