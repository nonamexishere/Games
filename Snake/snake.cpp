#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameOver = false;
int score;
int difficulty;
const int width = 20;
const int heigt = 20;
int x, y, fruitX, fruitY;
int tailX[width * heigt], tailY[width * heigt];
int sizeTail;
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;

void setup() {
    gameOver = false;
    score = 0;
    x = width / 2;
    y = heigt / 2;
    fruitX = rand() % width;
    fruitY = rand() % heigt;
    sizeTail = 0;
}

void scores() {
    cout << "Score: " << score << '\n';
}

void draw() {
    system("cls");
    for (int i = 0; i < width + 2; ++i) {
        cout << '#';
    }
    cout << '\n';
    for (int i = 0; i < heigt; ++i) {
        for (int j = 0; j < width + 2; ++j) {
            if (j == 0 || j == width + 1) cout << '#';
            else if (i == y && j == x) cout << 'O';
            else if (i == fruitY && j == fruitX) cout << 'X';
            else {
                bool isTail = false;
                for (int k = 0; k < sizeTail; ++k) {
                    if (i == tailY[k] && j == tailX[k]) {
                        cout << 'o';
                        isTail = true;
                    }
                }
                if (!isTail) cout << ' ';
            }
        }
        cout << '\n';
    }
    for (int i = 0; i < width + 2; ++i) {
        cout << '#';
    }
    cout << "\n\n";
}



void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            default:
                break;
        }
    }
}

void logic() {
    if (x == fruitX && y == fruitY) {
        score += difficulty;
        fruitX = (rand() % width) + 1;
        fruitY = rand() % heigt;
        sizeTail++;
    }
    int prevX = tailX[0], prevY = tailY[0];
    int prevXX, prevYY;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < sizeTail; ++i) {
        prevXX = tailX[i];
        prevYY = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevXX;
        prevY = prevYY;
    }
    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    for (int i = 0; i < sizeTail; ++i) {
        if (tailX[i] == x && tailY[i] == y) gameOver = true;
    }
    if (x == 0) x = width;
    if (x == width + 1) x = 1;
    if (y == -1) y = heigt - 1;
    if (y == heigt) y = 0;
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
    cout << "Use your \"W-A-S-D\" keys to move.\n";
    cout << "Game starts in: \n";
    cout << "5\n";
    Sleep(1000);
    cout << "4\n";
    Sleep(1000);
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
        Sleep(50 / difficulty);
    }
    draw();
    cout << "Your final score: " << score << '\n';
    Sleep(5000);
    return 0;
}