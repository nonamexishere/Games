#include <iostream>
#include <vector>
#include <string>
#ifndef PLAYER_HPP
#define PLAYER_HPP

using namespace std;

class player {
    private:
        string name;
        int score;
    public:
        player();
        player(string name);
        int getScore();
        string getName();
        void increaseScore();
        bool makeMove(vector<vector<char>>& grid, int row, int column, char symbol);
};

#endif