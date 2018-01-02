//
// Created by tomer on 02/01/18.
//

#include "CloseTheGames.h"
#include "GameManager.h"
#include "CommandsManager.h"
CloseTheGames :: CloseTheGames(Server * server) {
    this->s = s;
}

void CloseTheGames :: execute(vector<string> args) {
    CommandsManager commandsManager (this->s);
    GameManager *gm = GameManager::getInstance();
    vector <string> names = gm->GetNames();
    for (vector<string>::iterator iterator1 = names.begin(); iterator1 != names.end(); iterator1++) {
        vector <string> vec;
        vec.push_back(*iterator1);
        commandsManager.executeCommand("close", vec);
    }
}
CloseTheGames :: ~CloseTheGames() {

}