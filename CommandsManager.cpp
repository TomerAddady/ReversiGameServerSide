//
// Created by tomer on 24/12/17.
//
#include "CloseTheGames.h"
#include "CommandsManager.h"
#include "StartCommand.h"
#include "JoinCommand.h"
#include "GetGamesListCommand.h"
#include "CloseCommand.h"
#include "PlayCommand.h"

CommandsManager::CommandsManager(Server * s) {

    commandsMap["start"] = new StartCommand(s);
    commandsMap["join"] = new JoinCommand(s);
    commandsMap["list_games"] = new GetGamesListCommand(s);
    commandsMap["close"] = new CloseCommand(s);
    commandsMap["play"] = new PlayCommand();
    commandsMap["exit"] = new CloseTheGames(s);

}

CommandsManager::~CommandsManager() {
    map<string, Command *>::iterator it;
    for (it = commandsMap.begin(); it != commandsMap.end(); it++) {
        delete it->second;
    }
}

void CommandsManager::executeCommand(string command, vector<string> args) {
    cout << "executing the command: "<< command << endl;
    Command *commandObj = commandsMap[command];
    commandObj ->execute(args);
}