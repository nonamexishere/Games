#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "player.hpp"
#include "TicTacToe.hpp"
using namespace std;

int main() {
    TicTacToe* game;
    string player1, player2;
    cout << "Enter first player's name: "; cin >> player1;
    cout << "Enter second player's name: "; cin >> player2;
    player P1(player1);
    player P2(player2);
    game = new TicTacToe(P1, P2);
    cout << "****************************************\n";
    cout << "************GAME IS STARTING************\n";
    cout << "****************************************\n";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "LOADING... 12%\n";
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "LOADING... 67%\n";
    this_thread::sleep_for(chrono::milliseconds(1250));
    cout << "LOADING... 99%\n";
    bool is1 = 1;
    while (is1) {
        game->startGame();
        while (!game->getIsFinished()) {
            int r, c;
            cout << "Where do you want to make your move?\n";
            cout << "Select row: "; cin >> r;
            cout << "Select column: "; cin >> c;
            game->makeMove(r, c);
            game->nextTurn();
        }
        if (game->getIsFinished() == -1) {
            cout << "It is a tie!\nGood Luck! in the next round.\n";
            game->getPlayer1()->increaseScore();
            game->getPlayer2()->increaseScore();
        }
        else if (game->getTurn() & 1) {
            cout << game->getPlayer1()->getName() << " won the game, Congrats!\n";
            game->getPlayer1()->increaseScore();
        }
        else {
            cout << game->getPlayer2()->getName() << " won the game, Congrats!\n";
            game->getPlayer2()->increaseScore();
        }
        game->getScore();
        cout << "Would you like to continue?\n";
        cout << "Print 1 to continue or anything else to stop: "; cin >> is1;
    }
    return 0;
}