//
// Created by tomer on 05/12/17.
//

#include "Server.h"
#include <poll.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<iostream>
#include<stdio.h>
#include <arpa/inet.h>
#include <sstream>
#include "CommandsManager.h"
//#include "unistd.h"
//#include "arpa/inet.h"
using namespace std;
#define MAX_CONNECTED_CLIENTS 2
pthread_mutex_t ListOfThreadsMutex;


/**
 * Constractor.
 * @param port - we get number of the port.
 */
Server::Server(int port): port(port), serverSocket(0) {
   // this->commands_Manager_ = new CommandsManager();
    cout << "Server" << endl;
    this->shuoldRun = true;
}
Server :: ~Server() {
    //delete(this->commands_Manager_);

}

void Server::run() {



    this->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->serverSocket == -1) {
        throw ("error while creating socket!");
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(this->port);

    if (bind(this->serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        throw "Error on binding";
    }

    listen(this->serverSocket, MAX_CONNECTED_CLIENTS);

    pthread_t startThread;
    this->projectThreads.push_back(&startThread);
    pthread_create(&startThread, NULL, start, (void *)this);


    string command = "";
    while (command != "exit") {
        cin >> command;
    }



}


int Server ::closeServer() {
    CommandsManager commandsManager (this);
    vector <string> vec1;
    commandsManager.executeCommand("exit",vec1);
    close(this->serverSocket);
    this->Killthreads();
}
/**
 * Start the server.
 */
void *Server::start(void * clientObj) {
    cout << "in"<< endl;
    Server *s = (Server *) clientObj;
    // Create a socket point
/*
    s->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (s->serverSocket == -1) {
        throw ("error while creating socket!");
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(s->port);

    if (bind(s->serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        throw "Error on binding";
    }

    listen(s->serverSocket, MAX_CONNECTED_CLIENTS);
*/
    //pthread_t exitThread;
    //s->projectThreads.push_back(&exitThread); // adding the thread to server treads vector.
    //pthread_create(&exitThread, NULL, waitTillExit, (void *)s);

    while (true) {

        struct sockaddr_in client;
        socklen_t clienLen;


        cout << "Waiting for client connections..." << endl;
        int clientSocket = accept(s->serverSocket, (struct sockaddr *) &client, &clienLen);

        connectioObj *s1 = new connectioObj();
        s1->sd = clientSocket;
        s1->server = s;


        pthread_t threads;
        s->projectThreads.push_back(&threads); // adding the thread to server treads vector.
        pthread_create(&threads, NULL, handleClient, (void *)s1);
    }
    //the older implemntion of the function loop,
    /**     OLDER FROM EX4
    while (true) {
        struct sockaddr_in client1;
        struct sockaddr_in client2;
        socklen_t clien1Len;
        socklen_t clien2Len;
        //create first.
        char buff[] = "first";
        cout << "Waiting for client connections..." << endl;
        int clientSocket1 = accept(serverSocket, (struct sockaddr *) &client1, &clien1Len);
        //send wait to the first client for waiting to connect 2.
        cout << clientSocket1 << endl;
        int sentbytes = write(clientSocket1, "waiting", 100);
        cout << "Wrote waiting" << endl;

        if (sentbytes < 0) {
            throw "Error on sending";
        }
        int clientSocket2 = accept(serverSocket, (struct sockaddr *) &client2, &clien2Len);
        sentbytes = write(clientSocket1, "first", 100);
        if (sentbytes < 0) {
            throw "Error on sending";
        }
        sentbytes = write(clientSocket2, "second", 100);
        if (sentbytes < 0) {
            throw "Error on sending";
        }

        /*int sentbytes = write(clientSocket1, "first", 4096);
        if (sentbytes < 0) {
            throw "Error on sending";
        }
        unsigned int size = sizeof(struct sockaddr_in);
        char buffer[4096];
        bzero((void *) &buffer, sizeof(buffer));
        //int arg1;
        int bytes;

        int i = 2;
        bool endFlag = false;
        while (!endFlag) {
            if (i % 2 == 0) {
                bytes = read(clientSocket1, buffer, sizeof(buffer));
                endFlag = isClosed(bytes);
                if (strcmp(buffer, "END") != 0 && !endFlag) {
                    if (strcmp(buffer, "no_available_moves") != 0) {
                        sentbytes = write(clientSocket2, buffer, sizeof(buffer));
                        endFlag = isClosed(sentbytes);
                        bzero((void *) &buffer, sizeof(buffer));
                    } else {
                        i++;
                        continue;
                    }
                } else {
                    endFlag = true;
                }
            } else {
                bytes = read(clientSocket2, buffer, sizeof(buffer));
                endFlag = isClosed(bytes);

                if (strcmp(buffer, "END") != 0 && !endFlag) {
                    if (strcmp(buffer, "no_available_moves") != 0) {
                        sentbytes = write(clientSocket1, buffer, sizeof(buffer));
                        endFlag = isClosed(sentbytes);

                        bzero((void *) &buffer, sizeof(buffer));
                    } else {
                        i++;
                        continue;
                    }
                } else {
                    endFlag = true;
                }
            }
            //bzero((void *)&buffer, sizeof(buffer));

            i++;
        }
        cout << "end of game!"<< endl;
    //    delete(buff);
    }
    close(serverSocket);
    cout << "out of prog";

}*/
}

/*
void * Server ::waitTillExit(void *obj) {
    Server *s = (Server *) obj;
    string command = "";
    while (command != "exit") {
        cin >> command;
    }

    cout << "kill all threads:" << endl;
    // close all threads
    //pthread_mutex_lock(&threads_mutex);
    s->Killthreads();
    //pthread_mutex_unlock(&threads_mutex);

    // close all game rooms
    vector<string> args;
    args.push_back("");
    //CommandsManager commandsManager(this);
    //commandsManager.executeCommand("close_server", args);


   // this->shuoldRun = false;

}*/
int Server::Killthreads() {
    pthread_mutex_lock(&ListOfThreadsMutex);
    for (vector<pthread_t *>::iterator it = this->projectThreads.begin();
         it != this->projectThreads.end(); it++) {
            cout << "kill thread" << endl;
            pthread_cancel(**it);
    }
    pthread_mutex_unlock(&ListOfThreadsMutex);
}
void Server :: closeConnection(int sd) {
    close(sd);
}
int Server :: writeTo(int sd, const string& msg) {

    char buffer [BUFFER_SIZE];
    int  i;
    for (i = 0; i < msg.size(); i++) {
        buffer[i] = msg [i];
    }
    buffer[i] = '\0';

    int res = write(sd, buffer, BUFFER_SIZE);
    if (res == -1) {
        throw "Error on writing";
    }
    if (res == 0) {
        throw "Error client disconnected";
    }

}
int Server :: ReadFrom(int sd, char * buffer) {

    int res = read(sd, buffer, BUFFER_SIZE);
    if (res == -1) {
        throw "Error on reading";
    }
    if (res == 0) {
        throw "Error client disconnected";
    }
}


void * Server :: handleClient  (void * clientObj) {


    char buffer[BUFFER_SIZE];
    int bytes;
    connectioObj * s = (connectioObj*) clientObj;
    //bytes = read(s->sd, buffer, sizeof(buffer));
    try {
        s->server->ReadFrom(s->sd, buffer);
    } catch (const char * string1) {

    }
    CommandsManager commandsManager (s->server);


    std::string str(buffer);
    cout << buffer << endl;
    int index = str.find(" ");
    string str1 = str.substr(0, index);
    string str2 = str.substr(index + 1);
    vector <string> as ;

    stringstream s1;
    s1 << s->sd;
    string st = s1.str();

    as.push_back(st); // socket descriptor in string.
    as.push_back(str2); // name of game.

    commandsManager.executeCommand(str1, as);
    pthread_exit(NULL);
    //s->server->commands_Manager_->executeCommand(str1, as);

    //older possible implemention of handle client
    /**
    unsigned int size = sizeof(struct sockaddr_in);
    char buffer[4096];
    bzero((void *) &buffer, sizeof(buffer));
    //int arg1;
    int bytes;
    int sentbytes;

    int i = 2;
    bool endFlag = false;
    while (!endFlag) {
        if (i % 2 == 0) {
            bytes = read(clientSocket1, buffer, sizeof(buffer));
            endFlag = isClosed(bytes);
            if (strcmp(buffer, "END") != 0 && !endFlag) {
                if (strcmp(buffer, "no_available_moves") != 0) {
                    sentbytes = write(clientSocket2, buffer, sizeof(buffer));
                    endFlag = isClosed(sentbytes);
                    bzero((void *) &buffer, sizeof(buffer));
                } else {
                    i++;
                    continue;
                }
            } else {
                endFlag = true;
            }
        } else {
            bytes = read(clientSocket2, buffer, sizeof(buffer));
            endFlag = isClosed(bytes);

            if (strcmp(buffer, "END") != 0 && !endFlag) {
                if (strcmp(buffer, "no_available_moves") != 0) {
                    sentbytes = write(clientSocket1, buffer, sizeof(buffer));
                    endFlag = isClosed(sentbytes);

                    bzero((void *) &buffer, sizeof(buffer));
                } else {
                    i++;
                    continue;
                }
            } else {
                endFlag = true;
            }
        }
        //bzero((void *)&buffer, sizeof(buffer));

        i++;
    }
    cout << "end of game!"<< endl;
    //    delete(buff);
     */
}



bool Server  :: isClosed (int c) {
    if (c == -1) {
        cout << "Error writing or reading buffer" << endl;
        return true;
    }
    if (c == 0) {
        cout << "Client disconnected" << endl;
        return true;
    }
    return false;

}
