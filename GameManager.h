//
// Created by tomer on 26/12/17.
//

#ifndef SERVER_GAMEMANAGER_H
#define SERVER_GAMEMANAGER_H
#include<iostream>
#include <map>
#include <vector>
using namespace std;
#include "Game_Room.h"

class GameManager {
public:
    Game_Room *GetGameByName (string& s);
    static GameManager* getInstance();
    int addGame (Game_Room * game_room, string str);
    int removeGame (string name);
    vector<string> GetNames ();
    ~GameManager();
private:
    GameManager() {}
    static GameManager *instance;
    map<string, Game_Room*> gamesMap_; //name of game to the game obj.
};


#endif //SERVER_GAMEMANAGER_H
