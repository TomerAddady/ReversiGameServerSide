//
// Created by tomer on 24/12/17.
//

#include "CommandsManager.h"
#include "StartCommand.h"
#include "JoinCommand.h"
#include "GetGamesListCommand.h"
#include "CloseCommand.h"
#include "PlayCommand.h"

CommandsManager::CommandsManager() {

    commandsMap["start"] = new StartCommand();
    commandsMap["join"] = new JoinCommand();
    commandsMap["list_games"] = new GetGamesListCommand();
    commandsMap["close"] = new CloseCommand();
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