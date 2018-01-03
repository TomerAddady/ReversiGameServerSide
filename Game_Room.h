//
// Created by tomer on 26/12/17.
//

#ifndef SERVER_GAME_ROOM_H
#define SERVER_GAME_ROOM_H


#include "Server.h"

class Game_Room {
    private:

        int Firstsock;
        int Secondsock;
        int status; // 0 - not active 1 - active
        pthread_t *thread_;
        string name_;
    public:

        static void * manageTheGame (void * game_obj);
        Game_Room(int s1, string name);
        void JoinThegame (int s1, Server * server);
        int getFirstPlayerSock();
        int getSecondPlayerSock();
        int getStatus();
        string getName() const ;
        pthread_t *getThread() const;
        int isActive ();

};

typedef struct structForGame {
    Server * server; // socket descriptor
    Game_Room * gameRoom;
}GameObj;
#endif //SERVER_GAME_ROOM_H
