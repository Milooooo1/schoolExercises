#include "textInterface.hpp"

textInterface::textInterface(gameCore _game):
    game( _game )
{};

void textInterface::printState(){
    auto arr = game.getMoveList();
    std::array<std::array<int, 3>, 3> coordinates = {};
    std::array<int, 2> empty = {-1, -1};
    int pos = 0;
    for(auto & move : arr){
        if(move != empty){
            coordinates[move[0]][move[1]] = ((pos % 2 )+ 1);
        } else {
            coordinates[move[0]][move[1]] = 0;
        }
        pos++;
    }
    clear();
    for(int i = 0; i < 3; i++){
        std::cout << "\t";
        for(int j = 0; j < 3; j++){
            std::cout << coordinates[i][j] << " | ";
        }
        std::cout << "\n\t--|---|---|\n";
    }
}

void textInterface::mainLoop(){
    while(true){
        int res = game.checkWin();
        printState();
        if(res != 0){
            printState();
            if(res == 3){
                std::cout << "The game ended in a tie.\n";
            } else {
                std::cout << "Player: " << res << " has won the game!\n";
            }
            break;
        }
        bool validMove = false;
        while(!validMove){
            int row, col;
            std::cout << "What move would you like to do? 9 = undo last move.\nEnter row: ";
            std::cin >> row;
            if(row == 9){
                game.undoLastMove();
                break;
            }
            std::cout << "Column: ";
            std::cin >> col; 
            if(game.play(std::array<int,2>{row, col})){
                validMove = true;
            } else {
                std::cout << "Selected move is invalid. Try again.\n";
            }
        }
    }
}

void textInterface::start(){
    std::cout << "Game starting...\n";
    game.reset();
    mainLoop();
}