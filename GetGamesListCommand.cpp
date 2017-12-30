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
    GameManager * gameManager = GameManager :: getInstance();
    vector <string> s = gameManager->GetNames();

    // for all names write them to the client.
    for (vector <string> :: iterator iterator1 = s.begin(); iterator1 != s.end(); iterator1++ ) {
        try {
            this->s->writeTo(sd , *iterator1);

        } catch (const char * c) {
            this->s->closeConnection(sd);
            return;
        }
    }
    string s1 = "endLoop";
    this->s->writeTo(sd , s1);
    this->s->closeConnection(sd);// close connection after sending answer.
}

