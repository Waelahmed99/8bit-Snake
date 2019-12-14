#ifndef LOADERMANAGER_H_INCLUDED
#include <GL/glut.h>
#define UP   GLUT_KEY_UP
#define DOWN GLUT_KEY_DOWN
#define LEFT GLUT_KEY_LEFT
#define RIGHT GLUT_KEY_RIGHT
#define MAX_SIZE 60

void mapInit(int,int);
void drawMap();
void drawSingleSquare(int,int);
void drawSnakePlayer();
void drawEggs();

#endif // !LOADERMANAGER_H_INCLUDED
