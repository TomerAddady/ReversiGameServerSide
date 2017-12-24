//
// Created by tomer on 24/12/17.
//

#ifndef SERVER_PLAYCOMMAND_H
#define SERVER_PLAYCOMMAND_H

#include "Command.h"

class PlayCommand : public  Command {
    virtual void execute(vector<string> args);
    virtual ~PlayCommand();
};


#endif //SERVER_PLAYCOMMAND_H
