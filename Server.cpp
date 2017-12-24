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
//#include "unistd.h"
//#include "arpa/inet.h"
using namespace std;
#define MAX_CONNECTED_CLIENTS 2
/**
 * Constractor.
 * @param port - we get number of the port.
 */
Server::Server(int port): port(port), serverSocket(0) {
    this->commands_Manager_ = new CommandsManager();
    cout << "Server" << endl;
}
Server :: ~Server() {
    delete(this->commands_Manager_);

}


/**
 * Start the server.
 */
void Server::start() {
    // Create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw ("error while creating socket!");
    }
    // Assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *) &serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        throw "Error on binding";
    }

    listen(serverSocket, MAX_CONNECTED_CLIENTS);

    while (true) {

        struct sockaddr_in client;
        socklen_t clienLen;


        cout << "Waiting for client connections..." << endl;
        int clientSocket = accept(serverSocket, (struct sockaddr *) &client, &clienLen);
        pthread_t threads;
        pthread_create(&threads, NULL, handleClient, (void *)clientSocket);

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
void * Server :: handleClient  (void * clientSocket) {




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
