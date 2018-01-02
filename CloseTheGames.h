//
// Created by tomer on 02/01/18.
//

#ifndef SERVER_CLOSETHEGAMES_H
#define SERVER_CLOSETHEGAMES_H


#include "Command.h"
#include "Server.h"

class CloseTheGames: public Command{
    public:
        CloseTheGames(Server * server);
        virtual void execute(vector<string> args);
        virtual ~CloseTheGames ();
    private:
        Server * s;
};


#endif //SERVER_CLOSETHEGAMES_H
