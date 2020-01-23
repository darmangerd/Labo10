#include "gameEngine.h"

#include <algorithm>

void fruitSpawn(int& fruitX, int& fruitY, const int width, const int height, const GamePanel &gp)
 {
    srand ( time(NULL) );

    do {
        fruitX = rand() % width;
        fruitY = rand() % height;
    } while(gp.at(fruitY).at(fruitX) == OBSTACLE); // Bloque l'apparition d'un fruit sur un obstacle


}

void obstacleSpawn(const int width, const int height, GamePanel &gp, int nbObs, int posSnakeX, int posSnakeY) {
    srand ( time(NULL) );

    gp = GamePanel(height, std::vector<eObstacle>(width, CLEAR));

    for(int i = 0; i < nbObs; i++) {
        int y = rand() % (height-3) + 1;    // On ne spawn pas sur les bords
        int x = rand() % (width-3) + 1;

        if(gp.at(y).at(x) != OBSTACLE && y != posSnakeY && x != posSnakeX)  // ON assure qu'il y ait le nombre d'obstacle voulu et on ne spawn pas sur le serpend (départ uniquement)
            gp.at(y).at(x) = OBSTACLE;
        else
            i--;
    }
}

void logic(const int width,const int height, int& snakePosX, int& snakePosY, int& fruitPosX, int& fruitPosY, int& snakeSize, int tailX[], int tailY[], const eDirection direction, bool& gameover, const GamePanel &gp)
 {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = snakePosX;
    tailY[0] = snakePosY;

    for (int i = 1; i < snakeSize; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction)
    {
        case LEFT:
            snakePosX--;
            break;

        case RIGHT:
            snakePosX++;
            break;

        case UP:
            snakePosY--;
            break;

        case DOWN:
            snakePosY++;
            break;
    }

    // Test si la tête du serpent touche un bord. ou un obstacle
    if (snakePosX > width || snakePosX < 0 || snakePosY > height || snakePosY < 0 || gp.at(snakePosY).at(snakePosX) == OBSTACLE) {
        gameover = true;
    }

   // Test si le serpent se mord la queue
    for (int i = 0; i < snakeSize; i++) {
        if (tailX[i] == snakePosX && tailY[i] == snakePosY)
            gameover = true;
    }

    // Test si le serpent mange un Fruit
    if (snakePosX == fruitPosX && snakePosY == fruitPosY) {
        snakeSize++;
        fruitSpawn(fruitPosX,fruitPosY,width,height, gp);
    }
}