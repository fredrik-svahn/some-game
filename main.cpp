#include "./include/ECS.h"
#include "systems.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <ctime>
#include <iostream>
#include "WorldHandler.h"

using namespace ECS;

#define FPS 60

WorldHandler* handler = new WorldHandler();

clock_t begin = clock();
clock_t end = clock();

void display() {
    glutSwapBuffers();
}

void update(int value) {
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    end = clock();
    handler->getCurrent()->tick(end - begin);
    begin = clock();

    glutPostRedisplay();
    glutTimerFunc(1000 / FPS, update, 0);
}

int main(int argc, char** argv) {
    World* world = World::createWorld();
    handler->registerWorld("game", world);

    world->registerSystem(new MovementSystem());
    world->registerSystem(new SpriteSystem());

    Entity* e = world->create();
    e->assign<Sprite>(100,100);
    e->assign<Color>(1,1,0);
    e->assign<Velocity>(0.2,0,0);
    e->assign<Position>(0,0,0);

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

class ChangeWorldSubscriber : public EventSubscriber<ChangeWorldEvent> {
public:
    virtual ~ChangeWorldSubscriber() {}

    virtual void receive(World* world, const ChangeWorldEvent& event) {
        handler->currentWorld = event.world;
    }
};
