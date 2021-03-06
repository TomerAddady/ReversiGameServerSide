//
// Created by tomer on 24/12/17.
//

#include <sstream>
#include "JoinCommand.h"
#include "GameManager.h"
JoinCommand :: JoinCommand(Server * server) {
    this->s = server;
}
/**
 * inserting the other player to the requsted game.
 * @param args name at 0.
 */
void JoinCommand :: execute(vector<string> args) {
    int sd;
    string s = args.at(0); // socket descriptor at 0 and name at 1.
    istringstream istringstream1(s);
    istringstream1 >> sd;
    string name = args.at(1);
    GameManager * gm = GameManager :: getInstance();

    Game_Room * game_room = gm->GetGameByName(name);
    // if aroom requsted is not exist or already taken.
    if (game_room == NULL || game_room->getStatus() == 1) {
        try {
            this->s->writeTo(sd, "-1");
        }  catch (const char *message) {
            cout << message << endl;
            this->s->closeConnection(sd);
            return;
        }
        this->s->closeConnection(sd);
    } else {
        game_room->JoinThegame(sd, this->s);
        GameObj * parToGame = new GameObj;
        parToGame->gameRoom = game_room;
        parToGame->server = this->s;
        pthread_t thread;
       // pthread_create(&thread, NULL, Game_Room::manageTheGame, (void *)parToGame);// open new one to the game.
      //  this->s->addTaskToThreadPool(new Task(parToGame->gameRoom->manageTheGame, (void *)parToGame));
        this->s->addTaskToThreadPool(new Task(Game_Room::manageTheGame, (void *)parToGame));

    }
   // pthread_exit(NULL); // close the older pthread.
}
JoinCommand :: ~JoinCommand() {
}