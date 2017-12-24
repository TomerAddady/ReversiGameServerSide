//
// Created by tomer on 24/12/17.
//

#ifndef SERVER_JOINCOMMAND_H
#define SERVER_JOINCOMMAND_H

#include "Command.h"
class JoinCommand : public Command{
    friend class Server;
    virtual void execute(vector<string> args);
    virtual ~JoinCommand();
};


#endif //SERVER_JOINCOMMAND_H
