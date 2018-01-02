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

/**
 * runing the server listening to exit command.
 */
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

    /**
     * creating a thread for accept loop.
     */
    pthread_t startThread;
    this->projectThreads.push_back(&startThread);
    pthread_create(&startThread, NULL, start, (void *)this);

    /**
     * listening to exit commang from command line.
     */
    string command = "";
    while (command != "exit") {
        cin >> command;
    }



}

/**
 * closing the server nicely.
 * @return
 */
int Server ::closeServer() {
    CommandsManager commandsManager (this);
    vector <string> vec1;
    commandsManager.executeCommand("exit",vec1);
    close(this->serverSocket);
    this->Killthreads();
    return 1;
}
/**
 * Start the server.
 */
void *Server::start(void * clientObj) {
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

    /**
     * loop of accept.
     */
    struct sockaddr_in client;
    socklen_t clienLen = sizeof((struct sockaddr *)&client);

    while (true) {

        cout << "Waiting for client connections..." << endl;
        int clientSocket = accept(s->serverSocket, (struct sockaddr *) &client, &clienLen);

        connectioObj *s1 = new connectioObj();
        s1->sd = clientSocket;
        s1->server = s;

        /*
         * thread for handeling the accept that just arrived.
         */
        pthread_t threads;
        s->projectThreads.push_back(&threads); // adding the thread to server treads vector.
        pthread_create(&threads, NULL, handleClient, (void *)s1);
    }

}

/*
 * closing all the threads.
 */
int Server::Killthreads() {
    pthread_mutex_lock(&ListOfThreadsMutex);
    for (vector<pthread_t *>::iterator it = this->projectThreads.begin();
         it != this->projectThreads.end(); it++) {
            cout << "kill thread" << endl;
            pthread_cancel(**it);
    }
    pthread_mutex_unlock(&ListOfThreadsMutex);
}
/*
 * closing connction with the requested client.
 */
void Server :: closeConnection(int sd) {
    close(sd);
}
/**
 * writing message to the client/
 * @param sd clien to write.
 * @param msg message.
 * @return result of writing.
 */
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
/**
 * reading from client.
 * @param sd clien to read from.
 * @param buffer to write the message in.
 * @return result.
 */
int Server :: ReadFrom(int sd, char * buffer) {

    int res = read(sd, buffer, BUFFER_SIZE);
    if (res == -1) {
        throw "Error on reading";
    }
    if (res == 0) {
        throw "Error client disconnected";
    }
}

/**
 * calling the command requsted.
 * @param clientObj
 * @return
 */
void * Server :: handleClient  (void * clientObj) {


    char buffer[BUFFER_SIZE];
    int bytes;
    connectioObj * s = (connectioObj*) clientObj;
    //bytes = read(s->sd, buffer, sizeof(buffer));
    try {
        s->server->ReadFrom(s->sd, buffer);
    } catch (const char * string1) {
        cout << "failed to read from client." << endl;
        pthread_exit(NULL);
    }
    CommandsManager commandsManager (s->server);


    std::string str(buffer);
    //cout << buffer << endl;
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
