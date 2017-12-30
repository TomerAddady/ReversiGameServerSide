//
// Created by tomer on 24/12/17.
//

#ifndef SERVER_STARTCOMMAND_H
#define SERVER_STARTCOMMAND_H
#include "Command.h"
#include "Server.h"

class StartCommand : public Command{
    private:
        Server * s;
    virtual void execute(vector<string> args);
    virtual ~StartCommand();

public:
    StartCommand(Server * s);
};


#endif //SERVER_STARTCOMMAND_H
