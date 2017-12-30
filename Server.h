//
// Created by tomer on 05/12/17.
//

#ifndef SERVER3_SERVER_H
#define SERVER3_SERVER_H

#include <vector>
#include "iostream"
using namespace std;
//#include "CommandsManager.h"
//using namespace std;
#define BUFFER_SIZE 255



class Server {
public:
    Server(int port);
    ~Server();
    void start();
    void stop();
    static void * handleClient (void * clientObj);
    static void * waitTillExit (void * obj);
    void closeConnection (int sd);
    int writeTo(int sd, const string& msg);
    int ReadFrom(int sd, char * buffer);
    int Killthreads ();
private:
    vector<pthread_t *> projectThreads;
    int port;
    int serverSocket;// the socket's file descriptor
 //   CommandsManager * commands_Manager_;
    bool isClosed (int c);
//    bool shuoldRun;

    //  void handleClient(int clientSocket);
    //  int calc(int arg1, const char op, int arg2) const;
};

typedef struct connectioObj {
    int sd; // socket descriptor
    Server * server;
};

#endif //SERVER3_SERVER_H
