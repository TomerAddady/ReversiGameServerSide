//
// Created by tomer on 24/12/17.
//

#include <sstream>
#include "GetGamesListCommand.h"
#include "GameManager.h"


GetGamesListCommand :: GetGamesListCommand (Server * s) {
    this->s = s;
}
GetGamesListCommand :: ~GetGamesListCommand() {

}

void GetGamesListCommand :: execute(vector<string> args) {
    int sd;
    istringstream istringstream1(args.at(0));
    istringstream1 >> sd;
    cout << sd << endl;
    GameManager * gameManager = GameManager :: getInstance();
    vector <string> s = gameManager->GetNames();

    // for all names write them to the client.
    for (vector <string> :: iterator iterator1 = s.begin(); iterator1 != s.end(); iterator1++ ) {
        try {
            Game_Room * game_room = gameManager->GetGameByName(*iterator1);
            if (game_room->isActive() == 0) { // only if the game is not active.
                this->s->writeTo(sd, (*iterator1).c_str());
            }

        } catch (const char * c) {
            this->s->closeConnection(sd);
            return;
        }
    }
    char s1[8] = "endLoop";

    this->s->writeTo(sd , s1);
    this->s->closeConnection(sd);// close connection after sending answer.
}

