#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int height = 20;
const int width = 20;
int x,y,fx,fy,score;
int tailX[100], tailY[100];
int nTail;
enum edir {STOP = 0, LEFT, RIGHT, UP, DOWN};
edir dir;

void setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fx = rand() % width;
    fy = rand() % height;
    score = 0;

}
void draw() {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});
    for (int i=0; i < width+2; i++) {
    cout << "#";
    }
    cout << endl;
    for (int i=0; i < height; i++) {
        for (int j=0; j < width; j++) {
            if (j == 0) {
                cout << "#";
            }
            if (j == x && i == y) {
                cout << "O";
            }
            else if (j == fx && i == fy) {
                cout << "F";
            }
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                    
                }
                if (!print) {
                        cout << " ";
                    }
            }
            if (j == width-1) {
                cout << "#";
            }
        }
        cout << endl;
    }
    for (int i=0; i < width+2; i++) {
        cout << "#";
    }
    cout << endl;
    cout << "Score = " << score << endl;


}
void input() {
    if (_kbhit()) {
        switch(_getch()) {
            case 'w': 
                dir = UP;
                break;
            case 'a': 
                dir = LEFT;
                break;
            case 'd': 
                dir = RIGHT;
                break;
            case 's': 
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}
void logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 0; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch(dir) {
        case UP:
            y--;
            dir = STOP;
            break;
        case LEFT:
            x--;
            dir = STOP;
            break;
        case RIGHT:
            x++;
            dir = STOP;
            break;
        case DOWN:
            y++;
            dir = STOP;
            break;
    }
    if (x > width || x < 0 || y > height || y <0) {
        gameOver = true;
    }
    if (x == fx && y == fy) {
        score += 10;
        fx = rand() % width;
        fy = rand() % height;
        nTail++;
    }
    

}
int main() {
    setup();
    while (!gameOver) {
        draw();
        input();
        logic();
    }
    
    return 0;
}