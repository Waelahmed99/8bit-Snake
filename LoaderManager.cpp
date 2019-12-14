#include<GL/glut.h>
#include"LoaderManager.h"
#include <ctime>
#include<iostream>
#include<chrono>

// Map attributes.
const float DANGER_LINE_WIDTH = 2.0f;
const float NORMAL_LINE_WIDTH = 1.0f;
int mapX, mapY;

// Game attributes
int score;
extern bool isGameOver;
extern std::chrono::high_resolution_clock::time_point start;

// Snake attributes
int snakeX[60], snakeY[60];
int snakeLength;
int direction;

// Eggs attributes
int eggX, eggY;
bool isEggEaten = true;

void mapInit(int x, int y) { // initializing game.
    mapX = x, mapY = y;
    snakeLength = 4;
    direction = RIGHT;
    isGameOver = false;
    score = 0;
    for (int i = 0; i < snakeLength; i++)
        snakeX[i] = (x / 2), snakeY[i] = (y / 2) - i;
}

void drawMap() { // Draw the entire map blocks.
    for (int x_coord = 0; x_coord < mapX; x_coord++)
        for (int y_coord = 0; y_coord < mapY; y_coord++)
            drawSingleSquare(x_coord, y_coord);
}


bool isGoingToFall(int x, int y) { // returns true if the snake hit any border of the map.
    return (x == 0 || y == 0 || x == mapX - 1 || y == mapY - 1);
}

bool eggCollision() { // returns true if the snake ate the egg, false otherwise.
    return (snakeX[0] == eggX) && (snakeY[0] == eggY);
}

void drawSingleSquare(int x, int y) { // Draw single square from our map.
    glBegin(GL_POLYGON);

    if (isGoingToFall(x, y)) { // Dangerous squares attributes (Borders)
        glLineWidth(DANGER_LINE_WIDTH);
        glColor3f(1.0, 0.0, 0.0);
    }
    else { //Normal squares attributes.
        return;
    }

    glVertex2f(x, y);
    glVertex2f(x + 1, y);
    glVertex2f(x + 1, y + 1);
    glVertex2f(x, y + 1);

    glEnd();
}

void drawSnakePlayer() {
    for (int i = snakeLength - 1; i > 0 && !isGameOver; i--) { // Snake's body moving algorithm.
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // Change movement direction.
    if (direction == UP && !isGameOver) snakeY[0]++;
    else if (direction == DOWN && !isGameOver) snakeY[0]--;
    else if (direction == RIGHT && !isGameOver) snakeX[0]++;
    else if (direction == LEFT && !isGameOver) snakeX[0]--;

    for (int i = 0; i < snakeLength; i++) { // Create the snake
        if (i == 0) glColor3f(0.0, 0.7, 0.0);
        else glColor3f(0.0, 0.5, 0.0);
        glRectd(snakeX[i], snakeY[i], snakeX[i] + 1, snakeY[i] + 1);
    }

    if (isGoingToFall(snakeX[0], snakeY[0])) // The snake hit the border.
        isGameOver = true;

    if (eggCollision()) { // The snake ate the egg.
        isEggEaten = true;
        (snakeLength != MAX_SIZE ? snakeLength++ : snakeLength);
        score++;
        std::cout << "Your score is : " << score << std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> currTime = end - start;
    if (currTime.count() > 3) // To prevent collision at start (since the snake body overlaps at beginning)
        for (int i = 4; i < snakeLength - 1; i++) // start from 4 because the snake can't touch his first 3 body fragments.
            if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i])
                isGameOver = true;
}


void drawEggs() {
    if (isEggEaten) { // Generate new egg if the snake ate it.
        eggX = rand() % (mapX - 2) + 1;
        eggY = rand() % (mapY - 2) + 1;
    }
    isEggEaten = false;

    glColor3f(0.0, 1.0, 1.0);
    glRectd(eggX, eggY, eggX + 1, eggY + 1);
    glEnd();
}