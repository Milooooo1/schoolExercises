#include "gameCore.hpp"

#include <iostream> //DEBUGGING ONLY

gameCore::gameCore() {
    //Reset ply number on creation
    ply = 0; 
    for(long unsigned int i = 0; i < 9; i++){
        moveList[i] = {-1, -1};
    }
}

bool gameCore::undoLastMove(){
    if(ply != 0){
        ply--;
        moveList[ply] = {-1, -1};
        return 1;
    }
    return 0;
}

bool gameCore::isMoveValid(std::array<int, 2> _move){
    for(long unsigned int i = 0; i < 9; i++){
        if(moveList[i] == _move){
            return 0; //Check if move has already been set
        }
    }
    if(_move[0] > 2 || _move[1] > 2 ||  _move[0] < 0 ||  _move[1] < 0){
        return 0; //Check if its out of bounds. 
    }
    return 1;
}

bool gameCore::play(std::array<int, 2> _move){
    if( isMoveValid(_move) ){
        moveList[ply] = _move;
        ply++;
        return 1;
    }
    return 0;
}

int gameCore::checkWin(){
    std::array<int, 9> board = {0,0,0,0,0,0,0,0,0};
    auto arr = getMoveList();
    std::array<int, 2> empty = {-1, -1};
    for(long unsigned int i = 0; i < 9; i++){
        if(arr[i] == empty ){
            board[(arr[i][0] * 3) + arr[i][1]] = 0;
        } else {
            board[(arr[i][0] * 3) + arr[i][1]] = ((i % 2) + 1);
        }
    }

    //Check for wins
    for(int i = 1; i < 3; i++){ //Check for both players
        for(int j = 0; j < 3; j++){
            std::cout << "" << std::endl;
            if(board[j * 3] == i && board[(j * 3) + 1] == i && board[(j * 3) + 2] == i) {  //Check horizontal
                // std::cout << "Player: "<< (ply % 2) + 1 << " Won horizontally on row: "<< j << " \n";
                return i;
            } else if (board[j] == i && board[(j + 3)] == i && board[(j + 6)] == i) {      //Check vertical
                // std::cout << "Player: "<< (ply % 2) + 1 << " Won vertically on column: "<< j << " \n";
                return i;
            } 
        }
        if(board[0] == i && board[4] == i && board[8] == i){           //Check top left to bottom right
            // std::cout << "Player: "<< (ply % 2) + 1 << " Won top left to bottom right. \n";
            return i;
        } else if (board[2] == i && board[4] == i && board[6] == i) {  //Check top right to bottom left
            // std::cout << "Player: "<< (ply % 2) + 1 << " Won top right to bottom left. \n";
            return i; 
        }
    }

    if(ply == 9){
        return 3; //The game is a tie
    } else {
        return 0; //No winner yet
    }
}

std::array<std::array<int, 2>, 9> gameCore::getMoveList(){
    return moveList;
}

void gameCore::reset(){
    ply = 0; 
    for(long unsigned int i = 0; i < 9; i++){
        moveList[i] = {-1, -1};
    }
}