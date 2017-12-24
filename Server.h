//
// Created by tomer on 05/12/17.
//

#ifndef SERVER3_SERVER_H
#define SERVER3_SERVER_H

#include "CommandsManager.h"
using namespace std;

class Server {
public:
    Server(int port);
    ~Server();
    void start();
    void stop();
    static void * handleClient (void * clientSocket);
private:
    int port;
    int serverSocket;// the socket's file descriptor
    CommandsManager * commands_Manager_;
    bool isClosed (int c);
    //  void handleClient(int clientSocket);
    //  int calc(int arg1, const char op, int arg2) const;
};

#endif //SERVER3_SERVER_H
