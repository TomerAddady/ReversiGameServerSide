//
// Created by tomer on 26/12/17.
//

#include "GameManager.h"

GameManager* GameManager::instance = 0;
pthread_mutex_t GameMangerMapMutex; // mutex for the map
pthread_mutex_t ConstractMutex; // constractor mutex.

/**
 * @param s name of game.
 * @return the requsted game.
 */
Game_Room * GameManager :: GetGameByName (string& s) {
    pthread_mutex_lock(&GameMangerMapMutex);
    if (this->gamesMap_.count(s) > 0) {
        pthread_mutex_unlock(&GameMangerMapMutex);
        return  this->gamesMap_[s];
    }
    pthread_mutex_unlock(&GameMangerMapMutex);
    return NULL;
}

/**
 * destractor.
 */
GameManager :: ~GameManager() {
    // going over the gameRooms and deleting them.
    for (std::map<string, Game_Room *>::iterator it = this->gamesMap_.begin(); it != this->gamesMap_.end(); ++it) {
        delete (it->second);
    }
}

/**
 * @param name name of game to remove.
 * @return result.
 */
int GameManager ::removeGame(string name) {
    pthread_mutex_lock(&GameMangerMapMutex);
    if (this->gamesMap_.count(name) == 0) { // if not exist.
        pthread_mutex_unlock(&GameMangerMapMutex);
        return 0;
    }
    //GameRoom *gameRoom = this->gameRoomsMap_[gameRoomName];
    cout << "deleting the game : " << name << endl;
    Game_Room * game_room = this->gamesMap_[name];

    int res = this->gamesMap_.erase(name); // deleting the game from the list.

    delete(game_room); // deleting the game.
    pthread_mutex_unlock(&GameMangerMapMutex);
    return 0;
}

/**
 * @return vector of games names.
 */
vector<string> GameManager:: GetNames () {
    vector <string> s;
    pthread_mutex_lock(&GameMangerMapMutex);
    cout << "Game Manager list of names:" << endl;
    for (std::map<string, Game_Room*>::iterator it=this->gamesMap_.begin(); it!=this->gamesMap_.end(); ++it) {
        cout << it->first << endl;
        s.push_back(it->first);
    }
    pthread_mutex_unlock(&GameMangerMapMutex);
    return s;
}
/**
 * adding a game to the game map.
 * @param game_room game to add.
 * @param str name of the game.
 * @return result.
 */
int GameManager::addGame(Game_Room  *game_room, string str) {
  //  this->commandsMap[""] = game_room;
    pthread_mutex_lock(&GameMangerMapMutex);
    for (std::map<string, Game_Room*>::iterator it=this->gamesMap_.begin(); it!=this->gamesMap_.end(); ++it) {
        //std::cout << it->first << " => " << it->second << '\n';
        if (str == it->first) {
            pthread_mutex_unlock(&GameMangerMapMutex);
            return  -1;
        }
    }
    cout <<"adding game named: " << str << endl;
    gamesMap_[str] = game_room;
    pthread_mutex_unlock(&GameMangerMapMutex);

    return 1;
    //this->commandsMap[str] = game_room;
}
/*
 * returning the instace of the the singletone.
 */
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

