#ifndef TicTacToe_HPP
#define TicTacToe_HPP
#include <iostream>
#include <vector>
#include "player.hpp"

class TicTacToe {
    private:
        player* Player1;
        player* Player2;
        vector<vector<char>> grid;
        int turn;
        int isFinished = 0;
    public:
        TicTacToe();
        TicTacToe(player p1, player p2);
        player* getPlayer1();
        player* getPlayer2();
        void startGame();
        void getScore();
        int getTurn();
        void controlGameState();
        int getIsFinished();
        void printState();
        void makeMove(int row, int column);
        void nextTurn();
        void resetGame();
};


#endif