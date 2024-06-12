#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;

bool gameOver = false;
int score;
int difficulty;
const int width = 20;
const int height = 25;

class ball {
    private:
        int x, y, directionX, directionY, prevX, prevY;
    public:
        ball() : x(width / 2), y((height / 2) + (rand() % 10) - 5), directionX((rand() % 3) - 1), directionY(1) {}
        void move() {
            prevX = x;
            prevY = y;
            x += directionX;
            y += directionY;
        }
        void setDirectionX(int X) { // for plate
            if (X) directionX++;
            else directionX--;
            if (directionX > 2) directionX = 3;
            else if (directionX < -2) directionX = -3;
        } 
        void setDirectionX() {directionX = -directionX;} // for wall
        void setDirectionY() {directionY = -directionY;}
        int getX() {return x;}
        int getY() {return y;}
        void setX(int i) {x = i;}
        void setY(int i) {y = i;}
        int getPrevX() {return prevX;}
        int getPrevY() {return prevY;}
        int getDirectionX() {return directionX;}
        int getDirectionY() {return directionY;}
};

vector<vector<bool>> bricks(5, vector<bool>(width, true));
const int plateSize = 5;
vector<int> plates(plateSize);
enum eDirectionPlate {STOP = 0, LEFT, RIGHT};
eDirectionPlate dirPlate;

ball* BALL;
void setup() {
    BALL = new ball();
    gameOver = false;
    score = 0;
    plates[2] = width / 2;
    plates[1] = plates[2] - 1;
    plates[0] = plates[1] - 1;
    plates[3] = plates[2] + 1;
    plates[4] = plates[3] + 1;
}

void scores() {
    cout << "Score: " << score << '\n';
}

void draw() {
    system("cls");
    for (int i = 0; i < width + 2; ++i) {
        cout << '_';
    }
    cout << '\n';
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width + 2; ++j) {
            if (j == 0 || j == width + 1) cout << '|';
            else if (i < 5 && bricks[i][j - 1]) cout << 'O';
            else if (i == BALL->getY() && j == BALL->getX()) cout << 'o';
            else cout << ' ';
        }
        cout << '\n';
    }
    for (int i = 0; i < width + 2; ++i) {
        if (i == 0 || i == width + 1) cout << '|';
        else if (plates[0] == i) {cout << "_____"; i += 4;}
        else cout << ' ';
    }
    cout << "\n\n";
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dirPlate = LEFT;
                break;
            case 'd':
                dirPlate = RIGHT;
                break;
            case 's':
                dirPlate = STOP;
                break;
            default:
                break;
        }
    }
}

void logic() {
    switch (dirPlate) {
        case LEFT:
            for (int i = 0; i < plateSize; ++i) {
                if (i == 0 && plates[i] == 1) break;
                plates[i]--;
            }
            break;
        case RIGHT:
            for (int i = 0; i < plateSize; ++i) {
                if (i == 0 && plates[i] >= width + 1 - plateSize) break;
                plates[i]++;
            }
            break;
        case STOP:
            break;
        default:
            break;
    }

    if (BALL->getX() <= 0) {BALL->setDirectionX(); BALL->setX(0 - BALL->getX());}
    if (BALL->getX() >= width + 1) {BALL->setDirectionX(); BALL->setX(((width + 1) << 1) - BALL->getX());}
    if (BALL->getY() == -1) {BALL->setDirectionY(); BALL->setY(BALL->getPrevY());}
    if (BALL->getY() == height + 1) {
        bool isOnPlate = false;
        for (int& i : plates) {
            if (BALL->getX() == i) isOnPlate = true;
        }
        if (isOnPlate) {
            if (dirPlate)
                BALL->setDirectionX(dirPlate - 1);
            BALL->setDirectionY();
            BALL->setX(BALL->getPrevX());
            BALL->setY(BALL->getPrevY());
        }
        else gameOver = true;
    }

    if (BALL->getY() < 5) {
        int curr_x = BALL->getX();
        int curr_y = BALL->getY();
        int x = BALL->getPrevX();
        int y = BALL->getPrevY();
        int dirX = BALL->getDirectionX();
        int dirY = BALL->getDirectionY();
        bool isPos = abs(dirX) == dirX;
        if (dirX == 0) {
            if (bricks[curr_y][curr_x - 1]) {
                BALL->setDirectionY();
                score += difficulty;
                BALL->move();
                bricks[curr_y][curr_x - 1] = 0;
            }
        }
        else if (abs(dirX) == 1) {
            if (bricks[curr_y][x - 1] && bricks[y][curr_x - 1]) {
                BALL->setDirectionX();
                BALL->setDirectionY();
                score += (difficulty << 1);
                BALL->move();
                bricks[curr_y][x - 1] = 0;
                bricks[y][curr_x - 1] = 0;
            }
            else if (bricks[curr_y][x - 1]) {
                BALL->setDirectionY();
                BALL->move();
                score += difficulty;
                bricks[curr_y][x - 1] = 0;
            }
            else if (bricks[y][curr_x - 1]) {
                BALL->setDirectionX();
                BALL->move();
                score += difficulty;
                bricks[y][curr_x - 1] = 0;
            }
            else if (bricks[curr_y][curr_x - 1]) {
                BALL->setDirectionX();
                BALL->setDirectionY();
                score += difficulty;
                BALL->move();
                bricks[curr_y][curr_x - 1] = 0;
            }
        }
        else if (abs(dirX) == 2) {
            if (bricks[y][((curr_x + x) >> 1) - 1]) {
                BALL->setDirectionX();
                score += difficulty;
                BALL->move();
                bricks[y][((curr_x + x) >> 1) - 1] = 0;
            }
            else if (bricks[curr_y][((curr_x + x) >> 1) - 1] && bricks[y][curr_x - 1]) {
                BALL->setDirectionY();
                BALL->setDirectionX();
                score += (difficulty << 1);
                BALL->move();
                bricks[curr_y][((curr_x + x) >> 1) - 1] = 0;
                bricks[y][curr_x - 1] = 0;
            }
            else if (bricks[curr_y][((curr_x + x) >> 1) - 1]) {
                BALL->setDirectionY();
                score += difficulty;
                BALL->move();
                bricks[curr_y][((curr_x + x) >> 1) - 1] = 0;
            }
            else if (bricks[curr_y][curr_x - 1]) {
                BALL->setDirectionX();
                score += difficulty;
                BALL->move();
                bricks[curr_y][curr_x - 1] = 0;
            }
        }
        else if (abs(dirX) == 3) {
            if (isPos) {
                if (bricks[y][x]) {
                    BALL->setDirectionX();
                    score += difficulty;
                    BALL->move();
                    bricks[y][x] = 0;
                }
                else if (bricks[y][x + 1] && bricks[curr_y][x]) {
                    BALL->setDirectionX();
                    BALL->setDirectionY();
                    score += (difficulty << 1);
                    BALL->move();
                    bricks[y][x + 1] = 0;
                    bricks[curr_y][x] = 0;
                }
                else if (bricks[curr_y][x]) {
                    BALL->setDirectionY();
                    score += difficulty;
                    BALL->move();
                    bricks[curr_y][x] = 0;
                }
                else if (bricks[y][x + 1]) {
                    BALL->setDirectionX();
                    score += difficulty;
                    BALL->move();
                    bricks[y][x + 1] = 0;
                }
                else if (bricks[curr_y][x + 1]) {
                    BALL->setDirectionX();
                    BALL->setDirectionY();
                    score += (difficulty << 1);
                    BALL->move();
                    bricks[curr_y][x + 1] = 0;
                }
                else if (bricks[curr_y][curr_x - 1]) {
                    BALL->setDirectionX();
                    score += difficulty;
                    BALL->move();
                    bricks[curr_y][curr_x - 1] = 0;
                }
            }
            else {
                if (bricks[y][x - 2]) {
                    BALL->setDirectionX();
                    score += difficulty;
                    BALL->move();
                    bricks[y][x - 2] = 0;
                }
                else if (bricks[y][x - 3] && bricks[curr_y][x - 2]) {
                    BALL->setDirectionX();
                    BALL->setDirectionY();
                    score += (difficulty << 1);
                    BALL->move();
                    bricks[y][x - 3] = 0;
                    bricks[curr_y][x - 2] = 0;
                }
                else if (bricks[curr_y][x - 2]) {
                    BALL->setDirectionY();
                    score += difficulty;
                    BALL->move();
                    bricks[curr_y][x - 2] = 0;
                }
                else if (bricks[y][x - 3]) {
                    BALL->setDirectionX();
                    score += difficulty;
                    BALL->move();
                    bricks[y][x - 3] = 0;
                }
                else if (bricks[curr_y][x - 3]) {
                    BALL->setDirectionX();
                    BALL->setDirectionY();
                    score += (difficulty << 1);
                    BALL->move();
                    bricks[curr_y][x - 3] = 0;
                }
                else if (bricks[curr_y][curr_x - 1]) {
                    BALL->setDirectionX();
                    score += difficulty;
                    BALL->move();
                    bricks[curr_y][curr_x - 1] = 0;
                }
            }
        }
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
    cout << "Use your \"A-D\" keys to move and \"S\" key to stop.\n";
    cout << "Game starts in: \n";
    // cout << "5\n";
    // Sleep(1000);
    // cout << "4\n";
    // Sleep(1000);
    // cout << "3\n";
    // Sleep(1000);
    // cout << "2\n";
    // Sleep(1000);
    // cout << "1\n";
    // Sleep(1000);
    while(!gameOver) {
        draw();
        scores();
        input();
        logic();
        BALL->move();
        Sleep(500 / difficulty);
    }
    draw();
    cout << "Your final score: " << score << '\n';
    Sleep(5000);
    return 0;
}