//
// Created by tomer on 24/12/17.
//

#include "CloseCommand.h"
#include "GameManager.h"

CloseCommand ::  CloseCommand (Server * s) {
    this->s_ = s;
}
void CloseCommand :: execute(vector<string> args) {
    string gameRoomName = args.at(0);

    GameManager *gameRoomManeger = GameManager::getInstance();
    Game_Room * game_room = gameRoomManeger->GetGameByName(gameRoomName);
    int firstSocket = game_room->getFirstPlayerSock();
    int secondSocket = game_room->getSecondPlayerSock();
    this->s_->closeConnection(firstSocket);
    this->s_->closeConnection(secondSocket);
    gameRoomManeger->removeGame(gameRoomName);
}
CloseCommand :: ~CloseCommand() {

}