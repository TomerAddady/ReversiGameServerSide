//
// Created by tomer on 24/12/17.
//

#include <sstream>
#include "JoinCommand.h"
#include "GameManager.h"
JoinCommand :: JoinCommand(Server * server) {
    this->s = s;
}
void JoinCommand :: execute(vector<string> args) {
    int sd;
    string s = args.at(0); // socket descriptor at 0 and name at 1.
    cout << "im in join1" << endl;
    cout << s << endl;
    istringstream istringstream1(s);
    istringstream1 >> sd;
    string name = args.at(1);
    GameManager * gm = GameManager :: getInstance();

    Game_Room * game_room = gm->GetGameByName(name);
    // if aroom requsted is not exist or already taken.
    if (game_room == NULL || game_room->getStatus() == 1) {
        cout << "get in the if"<<endl;
        try {
            this->s->writeTo(sd, "-1");
        }  catch (const char *message) {
            cout << message << endl;
            this->s->closeConnection(sd);
            return;
        }
        this->s->closeConnection(sd);
    } else {
     /*   try {
            //this->s->writeTo(sd, "1");
        } catch (const char *message) {
            cout << message << endl;
            this->s->closeConnection(sd);
            return;
        }*/
        game_room->JoinThegame(sd, this->s);
        GameObj * parToGame = new GameObj;
        parToGame->gameRoom = game_room;
        parToGame->server = this->s;
        pthread_t thread;
        pthread_create(&thread, NULL, Game_Room::manageTheGame, (void *)parToGame);// open new one to the game.
    }
    pthread_exit(NULL); // close the older pthread.
    //pthread_create(parToGame->gameRoom->getThread(), NULL ,parToGame->gameRoom->manageTheGame, (void *)parToGame);
}
JoinCommand :: ~JoinCommand() {
}