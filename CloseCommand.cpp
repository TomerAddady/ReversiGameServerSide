//
// Created by tomer on 24/12/17.
//

#include "CloseCommand.h"
#include "GameManager.h"

CloseCommand ::  CloseCommand (Server * s) {
    this->s_ = s;
}
/**
 * closing the requsted game.
 * @param args the game name is at 0.
 */
void CloseCommand :: execute(vector<string> args) {
    string gameRoomName = args.at(0);
    cout << "closing game : " << gameRoomName << endl;
    GameManager *gameRoomManeger = GameManager::getInstance();
    Game_Room * game_room = gameRoomManeger->GetGameByName(gameRoomName);
    int firstSocket = game_room->getFirstPlayerSock();
    int secondSocket = game_room->getSecondPlayerSock();
    /*
     * if the sockets not closed alreay than close them.
     */
    if (firstSocket != -1) {
        this->s_->closeConnection(firstSocket);
    }
    if (secondSocket != -1) {
        this->s_->closeConnection(secondSocket);
    }
    gameRoomManeger->removeGame(gameRoomName);
}
CloseCommand :: ~CloseCommand() {

}