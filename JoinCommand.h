//
// Created by tomer on 24/12/17.
//

#ifndef SERVER_JOINCOMMAND_H
#define SERVER_JOINCOMMAND_H

#include "Server.h"
#include "Command.h"
class JoinCommand : public Command{
    public:
        JoinCommand(Server * server);
        virtual void execute(vector<string> args);
        virtual ~JoinCommand();
    private:
        Server * s;
};


#endif //SERVER_JOINCOMMAND_H
