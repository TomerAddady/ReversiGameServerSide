//
// Created by tomer on 24/12/17.
//

#include <sstream>
#include "StartCommand.h"
#include "GameManager.h"
pthread_mutex_t Startmutex;

StartCommand :: ~StartCommand() {

}

void StartCommand :: execute(vector<string> args) {
    int sd;
    string gameName;
    cout << "im in start" << endl ;
    istringstream istringstream1(args.at(0));
    istringstream1 >> sd;
    gameName = args.at(1);
    GameManager * gm = GameManager :: getInstance();

    Game_Room* g = new Game_Room(sd, gameName);
    cout << gameName << "\n";
    int res = gm->addGame(g,gameName);
    if (res == 1) {
        try {
            string s = "waiting";
            this->s->writeTo(sd, s);
        } catch (const char * string1) {

        }
    } else if (res == -1) {
        this->s->closeConnection(sd);
    }
}
StartCommand :: StartCommand(Server * server) {
    this->s = server;
}