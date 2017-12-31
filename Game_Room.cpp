//
// Created by tomer on 26/12/17.
//

#include <cstring>
#include <vector>
#include "Game_Room.h"
#include "CommandsManager.h"
#include "GameManager.h"

Game_Room :: Game_Room(int s1, string name) {
    this->Firstsock = s1;
    this->name_ = name;
    this->status = 0; // game not active yet.
    //this->Secondsock = s2;
}


pthread_t* Game_Room::getThread() const {
    this->thread_;
}
string Game_Room::getName() const  {
    return this->name_;
}
void * Game_Room::manageTheGame (void * game_obj) {
    GameObj * gameObj = (GameObj *) game_obj;
    Game_Room * gr = gameObj->gameRoom;
    Server * s = gameObj->server;
    int firstPlayerSD = gameObj->gameRoom->getFirstPlayerSock();
    int secondPlayerSD = gameObj->gameRoom->getSecondPlayerSock();
    cout<< "write"<<endl;
    try {
        s->writeTo(firstPlayerSD, "first");
        cout << "now were writing for the first";
        // telling the first player that he is the first (he is x)
        s->writeTo(secondPlayerSD, "second"); //telling the second player that he is the second (he is o)

    } catch (char * s) {
        cout << "now were catch for the first";

    }
    char buffer [BUFFER_SIZE];
    int i = 2;
    bool endFlag = false;
    while (!endFlag) {
        if (i % 2 == 0) {
            //bytes = read(clientSocket1, buffer, sizeof(buffer));
            try {
                s->ReadFrom(firstPlayerSD, buffer);
            } catch (const char * x) {
                endFlag = true;
                continue;
            }
            try {
                s->writeTo(secondPlayerSD, buffer);
                // need to check if end.
            } catch (const char * x) {
                endFlag = true;
                continue;
            }
            bzero((void *) &buffer, sizeof(buffer));

        } else {
            try {
                s->ReadFrom(secondPlayerSD, buffer);
            } catch (const char * x) {
                endFlag = true;
                continue;
            }
            try {
                s->writeTo(firstPlayerSD, buffer);
            } catch (const char * x) {
                endFlag = true;
                continue;
            }
        }
        i++;
    }
    CommandsManager * commandsManager = new CommandsManager(s);
    vector <string> nameVec;
    nameVec.push_back(gr->getName());

    commandsManager->executeCommand("close", nameVec);
    //GameManager *gameRoomsController = GameManager::getInstance();
    // removing and deliting this game from the list.
    //gameRoomsController->removeGame(gr->getName());
//    pthread_exit(NULL); // close the older pthread.

}

void Game_Room :: JoinThegame(int s, Server * server) {
    try {
        //server->writeTo(this->getFirstPlayerSock(), "first");
    } catch (const char * x) {

    }
    this->Secondsock = s;

    this->status = 1; // game is active now.
}
int Game_Room :: getFirstPlayerSock() {
    return this->Firstsock;
}
int Game_Room :: getSecondPlayerSock() {
    return this->Secondsock;
}
int Game_Room :: getStatus() {
    return this->status;
}