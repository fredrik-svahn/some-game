#include "./include/ECS.h"
#include "systems.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <ctime>
#include <iostream>

using namespace ECS;

World* world = World::createWorld();

clock_t begin = clock();
clock_t end = clock();

void display() {

    glutSwapBuffers();
}

void update(int value) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    end = clock();
    world->tick(end - begin);
    begin = clock();

    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}

int main(int argc, char** argv) {
    world->registerSystem(new MovementSystem());
    world->registerSystem(new SpriteSystem());

    Entity* e = world->create();
    e->assign<Sprite>(50,50);
    e->assign<Color>(1,0,0);
    e->assign<Velocity>(0.01,0.01);
    e->assign<Position>(0,0);

    glutInit(&argc, argv);
    glutInitWindowSize(1000, 1000);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Arpg game");
    update(0);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
