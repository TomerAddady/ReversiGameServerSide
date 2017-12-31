//
// Created by tomer on 26/12/17.
//

#include "GameManager.h"

GameManager* GameManager::instance = 0;
pthread_mutex_t GameMangerMapMutex;
pthread_mutex_t ConstractMutex;


Game_Room * GameManager :: GetGameByName (string& s) {
    pthread_mutex_lock(&GameMangerMapMutex);
    if (this->map1.count(s) > 0) {
        pthread_mutex_unlock(&GameMangerMapMutex);
        return  this->map1[s];
    }
    pthread_mutex_unlock(&GameMangerMapMutex);
    return NULL;
}

GameManager :: ~GameManager() {
    // going over the gameRooms and deleting them.
    for (std::map<string, Game_Room *>::iterator it = this->map1.begin(); it != this->map1.end(); ++it) {
        delete (it->second);
    }
}


int GameManager ::removeGame(string name) {
    pthread_mutex_lock(&GameMangerMapMutex);
    if (this->map1.count(name) == 0) { // if not exist.
        pthread_mutex_unlock(&GameMangerMapMutex);
        return 0;
    }
    //GameRoom *gameRoom = this->gameRoomsMap_[gameRoomName];
    this->map1.erase(name); // deleting the game from the list.
    delete(this->map1[name]); // deleting the game.
    pthread_mutex_unlock(&GameMangerMapMutex);
    return 0;
}

vector<string> GameManager:: GetNames () {
    vector <string> s;
    pthread_mutex_lock(&GameMangerMapMutex);
    for (std::map<string, Game_Room*>::iterator it=this->map1.begin(); it!=this->map1.end(); ++it) {
        s.push_back(it->first);
    }
    pthread_mutex_unlock(&GameMangerMapMutex);
    return s;
}

int GameManager::addGame(Game_Room  *game_room, string str) {
  //  this->commandsMap[""] = game_room;
    pthread_mutex_lock(&GameMangerMapMutex);
    for (std::map<string, Game_Room*>::iterator it=this->map1.begin(); it!=this->map1.end(); ++it) {
        //std::cout << it->first << " => " << it->second << '\n';
        if (str == it->first) {
            pthread_mutex_unlock(&GameMangerMapMutex);
            return  -1;
        }
    }
    map1[str] = game_room;
    pthread_mutex_unlock(&GameMangerMapMutex);

    return 1;
    //this->commandsMap[str] = game_room;
}
Game_Room & GameManager:: getGame (string name) {

}




GameManager* GameManager::getInstance() {

    if(!instance) {
        pthread_mutex_lock(&ConstractMutex);
        instance = new GameManager();
        pthread_mutex_unlock(&ConstractMutex);
        return instance;
    } else {
        return instance;
    }
}

