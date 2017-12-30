//
// Created by tomer on 24/12/17.
//

#ifndef SERVER_CLOSECOMMAND_H
#define SERVER_CLOSECOMMAND_H

#include "Server.h"
#include "Command.h"

class CloseCommand : public Command {
private:
    Server * s_;
    virtual void execute(vector<string> args);
    virtual ~CloseCommand();

public:
    CloseCommand(Server * s);

};


#endif //SERVER_CLOSECOMMAND_H
