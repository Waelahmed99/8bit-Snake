#include<GL/glut.h>
#include<iostream>
#include"LoaderManager.h"
#include<chrono>
#include<string>
#include <cstring>
#include <iomanip>
#include <thread>

#define COLUMNS 40
#define ROWS 40

using namespace std;

// Global variables from LoaderManager.
extern int direction;
extern int score;
bool isGameOver = false;
std::chrono::high_resolution_clock::time_point start;

// Speed of snake (determine the FPS timer)
float speed = 10;

bool firstTime = true;

// Initialize background and the grid.
void init() {
    glClearColor(0,0,0,1);
    mapInit(COLUMNS, ROWS);
}

// Function to print Text on screen.
void output(int x, int y, const char *string)
{
    int len, i;

    glColor3f(1.0,1.0,0);
    glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, string[i]);
    }
}

// Startup menu
void welcomeScreen() {
    output(13, 20, "Welcome to 8bit snake :)");
    output(15, 18, "Use arrows to move");
    output(13, 17, "And X to start/restart game");
}

// Display function for drawing.
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawMap(); // Draw the map
    drawSnakePlayer(); // Draw the playable snake
    drawEggs(); // Draw eggs (to be eaten)

    if (firstTime)
        welcomeScreen();

    float currSpeed = speed + (score/2.0);
    std::stringstream stream;
    stream << std::fixed << std::setprecision(1) << currSpeed;
    output(0,39, ("score: " + to_string(score)).c_str());
    output(0,0, ("speed: " + stream.str()).c_str());

    // Player ate himself || hit borders
    if (isGameOver) {
        output(17,20, "Game over!");
        output(10,19, ("Your score: " + to_string(score) + " your speed: " + stream.str()).c_str());
        output(14,17, "Press X to restart");
        cout << "Game over! your score is: " << score << " and your speed: " << (speed + (score/2.0)) << endl;
        cout << "Press X to restart\n";
    }

    glutSwapBuffers();
}

// Create the Viewport
void reshape(int w, int h) {
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, COLUMNS, 0, ROWS, -1, 1);
}

// Timer to redraw shapes.
void timer(int) {
    if (!isGameOver && !firstTime)
        glutPostRedisplay();
    glutTimerFunc(1000/(speed + (score/2.0)), timer, 0);
}

// Keyboard listener handler.
void keyboardSpec(const int key, int x, int y) {
    // prevent snake to move over his body!
    if ((key == LEFT && direction == RIGHT) || (key == UP && direction == DOWN) || (key == direction) ||
        (key == RIGHT && direction == LEFT) || (key == DOWN && direction == UP)) return;

    switch (key) {
        case UP:
        case DOWN:
        case LEFT:
        case RIGHT:
            direction = key; // Assign the direction (Global variable).
            break;
        case 'x':
            mapInit(ROWS, COLUMNS);
            break;
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'x':
            firstTime = false;
            mapInit(ROWS, COLUMNS);
            cout << "\nNew game started\n";
            break;
    }
}

int main(int argc, char** argv)
{
    start = std::chrono::high_resolution_clock::now();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("8bit Snake");
    init();
    cout << "\nNew game started\n";

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutSpecialFunc(keyboardSpec);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}