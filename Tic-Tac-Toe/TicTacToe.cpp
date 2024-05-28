#include "TicTacToe.hpp"
#include <iostream>

TicTacToe::TicTacToe() {
    Player1 = new player("Player1");
    Player2 = new player("Player2");
    turn = 0;
    grid = {{'#','|', '#', '|', '#'}, 
            {'-', '-', '-', '-', '-'}, 
            {'#','|', '#', '|', '#'}, 
            {'-', '-', '-', '-', '-'}, 
            {'#','|', '#', '|', '#'}};
}
TicTacToe::TicTacToe(player p1, player p2) {
    Player1 = &p1;
    Player2 = &p2;
    turn = 0;
    grid = {{'#','|', '#', '|', '#'}, 
            {'-', '-', '-', '-', '-'}, 
            {'#','|', '#', '|', '#'}, 
            {'-', '-', '-', '-', '-'}, 
            {'#','|', '#', '|', '#'}};
}
player* TicTacToe::getPlayer1() {
    return Player1;
}
player* TicTacToe::getPlayer2() {
    return Player2;
}
void TicTacToe::startGame() {
    cout << "****************************************\n";
    cout << Player1->getName() << " vs " << Player2->getName() << '\n';
    getScore();
    cout << "****************************************\n\n\n";
    resetGame();
    printState();
}
void TicTacToe::getScore() {
    cout << "Current Score: " << Player1->getScore() << " - " << Player2->getScore() << '\n';
}
int TicTacToe::getTurn() {
    return turn;
}
void TicTacToe::controlGameState() {
    if (grid[0][0] == grid[0][2] && grid[0][4] == grid[0][2] && grid[0][2] != '#') isFinished = 1;
    if (grid[2][0] == grid[2][2] && grid[2][4] == grid[2][2] && grid[2][2] != '#') isFinished = 1;
    if (grid[4][0] == grid[4][2] && grid[4][4] == grid[4][2] && grid[4][2] != '#') isFinished = 1;
    if (grid[0][0] == grid[2][0] && grid[4][0] == grid[2][0] && grid[2][0] != '#') isFinished = 1;
    if (grid[0][2] == grid[2][2] && grid[4][2] == grid[2][2] && grid[2][2] != '#') isFinished = 1;
    if (grid[0][4] == grid[2][4] && grid[4][4] == grid[2][4] && grid[2][4] != '#') isFinished = 1;
    if (grid[0][0] == grid[2][2] && grid[4][4] == grid[2][2] && grid[2][2] != '#') isFinished = 1;
    if (grid[0][4] == grid[2][2] && grid[4][0] == grid[2][2] && grid[2][2] != '#') isFinished = 1;
    if (turn == 8) isFinished = -1;
}
int TicTacToe::getIsFinished() {
    return isFinished;
}
void TicTacToe::printState() {
    cout << "***********CURRENT GAME STATE***********\n\n";
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
}
void TicTacToe::makeMove(int row, int column) {
    int r = row, c = column;
    if (turn & 1) {
        while(!Player2->makeMove(grid, r - 1, c - 1, 'O')) {
            cout << "Please enter a valid point.\n";
            cout << "Row: "; cin >> r;
            cout << "Column: "; cin >> c;
        }
    }
    else {
        while(!Player1->makeMove(grid, r - 1, c - 1, 'X')) {
            cout << "Please enter a valid point.\n";
            cout << "Row: "; cin >> r;
            cout << "Column: "; cin >> c;
        }
    }
    
    controlGameState();
    printState();
}
void TicTacToe::nextTurn() {
    turn++;
}
void TicTacToe::resetGame() {
    grid = {{'#','|', '#', '|', '#'}, 
            {'-', '-', '-', '-', '-'}, 
            {'#','|', '#', '|', '#'}, 
            {'-', '-', '-', '-', '-'}, 
            {'#','|', '#', '|', '#'}};
    turn = 0;
    isFinished = 0;
}