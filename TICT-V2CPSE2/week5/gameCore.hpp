#ifndef _GAMECORE_HPP
#define _GAMECORE_HPP

#include <array>

class gameCore {
private:
    int ply;
    std::array<std::array<int, 2>, 9> moveList = {}; 
    // int moveList [9][2] = {}; //std::array

    // Checks if a given move is valid.
    bool isMoveValid(std::array<int, 2> _move);

public:
    gameCore();

    // This function removes the last move, it
    // return a 1 if succesfull and a 0 if its not.
    bool undoLastMove();

    // This function plays a new move. It returns
    // a 1 if succesfull and a 0 if its not. 
    bool play(std::array<int, 2> _move);

    // This function checks if there is a winner, it
    // return a 0 if there are no winners, a 1 if 
    // player 1 won and a 2 if player 2 won. If the
    // game ends up in a tie the function returns 3.
    int checkWin();

    // Returns the list of moves that have been played
    std::array<std::array<int, 2>, 9> getMoveList();

    //Resets all the local variables
    void reset();

};

#endif //_GAMECORE_HPP