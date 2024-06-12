#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver = false;
int score;
int difficulty;
const int width = 30;
const int height = 30;
int x, y;
int pipeX, pipeY;
enum eDirection {STOP = 0, UP, DOWN};
eDirection dir;

void setup() {
    gameOver = false;
    score = 0;
    x = 2;
    pipeX = width - 2;
    pipeY = rand() % (height - 3) + 2;
    y = height / 2;
    dir = DOWN;
}

void scores() {
    cout << "Score: " << score << '\n';
}

void draw() {
    system("cls");
    cout << '\n';
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width + 2; ++j) {
            if (j == pipeX) {
                if (i == y && j == x) cout << 'Q';
                else if (i == pipeY - 1 || i == pipeY + 1 || i == pipeY) cout << ' ';
                else cout << '#';
            }
            else if (i == y && j == x) cout << 'Q';
            else cout << ' ';
        }
        cout << '\n';
    }
    cout << "\n\n";
}



void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'w':
                dir = UP;
                break;
            default:
                break;
        }
    }
}

void logic() {
    if (x == pipeX) {
        if (y == pipeY || y == pipeY - 1 || y == pipeY + 1) {
            pipeX = width - 2;
            pipeY = rand() % (height - 3) + 2;
            score += difficulty;
        }
        else {
            gameOver = true;
        }
    }
    else {
        pipeX--;
    }
    switch (dir) {
        case UP:
            y--;
            dir = DOWN;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if (y == -1 || y == height) {
        gameOver = true;
    }
}


int main() {
    srand(time(NULL));
    setup();
    cout << "Choose difficulty level: (1-Easiest 5-Hardest)";
    cin >> difficulty;
    if (difficulty > 5 || difficulty < 1) {
        cout << "Your difficulty set as 5\n";
        difficulty = 5;
    }
    cout << "*************HOW TO PLAY*************\n";
    cout << "Use your \"W\" key to jump.\n";
    cout << "Game starts in: \n";
    cout << "3\n";
    Sleep(1000);
    cout << "2\n";
    Sleep(1000);
    cout << "1\n";
    Sleep(1000);
    while(!gameOver) {
        draw();
        scores();
        input();
        logic();
        Sleep(720 / difficulty);
    }
    draw();
    cout << "Your final score: " << score << '\n';
    Sleep(5000);
    return 0;
}