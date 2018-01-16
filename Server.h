//
// Created by tomer on 05/12/17.
//

#ifndef SERVER3_SERVER_H
#define SERVER3_SERVER_H

#include <vector>
#include "iostream"
#include "ThreadPool.h"
using namespace std;
//#include "CommandsManager.h"
//using namespace std;
#define BUFFER_SIZE 255



class Server {
public:
    Server(int port);
    ~Server();
    static void * start(void * clientObj);
    void stop();
    static void * handleClient (void * clientObj);
    void run ();
    void closeConnection (int sd);
    int writeTo(int sd, const string& msg);
    int ReadFrom(int sd, char * buffer);
    void addTaskToThreadPool (Task * task);
    int Killthreads ();
    int closeServer ();
private:
    vector<pthread_t *> projectThreads;
    int port;
    int serverSocket;// the socket's file descriptor
 //   CommandsManager * commands_Manager_;
    ThreadPool threadPool_;
    bool isClosed (int c);
    bool shuoldRun;

    //  void handleClient(int clientSocket);
    //  int calc(int arg1, const char op, int arg2) const;
};

typedef struct structForCon{
    int sd; // socket descriptor
    Server * server;
}connectioObj;

#endif //SERVER3_SERVER_H
