//
// Created by tomer on 24/12/17.
//

#ifndef SERVER_GETGAMESLISTCOMMAND_H
#define SERVER_GETGAMESLISTCOMMAND_H

#include "Command.h"
class GetGamesListCommand : public Command {
    virtual void execute(vector<string> args);
    virtual ~GetGamesListCommand();
};


#endif //SERVER_GETGAMESLISTCOMMAND_H
