//
// Created by tomer on 24/12/17.
//

#ifndef SERVER_STARTCOMMAND_H
#define SERVER_STARTCOMMAND_H

#include "Command.h"
class StartCommand : public Command{
    virtual void execute(vector<string> args);
    virtual ~StartCommand();
};


#endif //SERVER_STARTCOMMAND_H
