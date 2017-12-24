//
// Created by tomer on 24/12/17.
//

#ifndef SERVER_CLOSECOMMAND_H
#define SERVER_CLOSECOMMAND_H

#include "Command.h"

class CloseCommand : public Command {
    virtual void execute(vector<string> args);
    virtual ~CloseCommand();
};


#endif //SERVER_CLOSECOMMAND_H
