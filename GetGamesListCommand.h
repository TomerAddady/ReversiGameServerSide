//
// Created by tomer on 24/12/17.
//

#ifndef SERVER_GETGAMESLISTCOMMAND_H
#define SERVER_GETGAMESLISTCOMMAND_H

#include "Command.h"
#include "Server.h"
class GetGamesListCommand : public Command {
    public:
        GetGamesListCommand (Server * s);
        virtual void execute(vector<string> args);
        virtual ~GetGamesListCommand();

    private:
        Server * s;
};


#endif //SERVER_GETGAMESLISTCOMMAND_H
