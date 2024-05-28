#include "player.hpp"

player::player() {
    name = "unknown";
    score = 0;
}
player::player(string name) {
    this->name = name;
    score = 0;
}
int player::getScore() {
    return score;
}
string player::getName() {
    return name;
}
void player::increaseScore() {
    score++;
}
bool player::makeMove(vector<vector<char>>& grid, int row, int column, char symbol) {
    int r = row << 1, c = column << 1;
    if (r > 4 || r < 0 || c > 4 || c < 0) return false;
    if (grid[r][c] != '#') return false;
    grid[r][c] = symbol;
    return true;
}
