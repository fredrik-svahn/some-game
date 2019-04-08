#include "World.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

engine::World* world = new engine::World();

struct Status : engine::Component {
    bool alive;
};

struct Position : engine::Component {
    Position(double x, double y): x(x), y(y) {}
    double x;
    double y;
};

struct Velocity : engine::Component {
    Velocity(double x, double y): x(x), y(y) {}
    double x;
    double y;
};

struct Color {
    double r;
    double g;
    double b;
    double a;
};

struct RenderRectangle : engine::Component {
    RenderRectangle(double w, double h, Color color): w(w), h(h), color(color) {}
    double w;
    double h;
    Color color;
};

void stuff() {
    auto list = world->subset({"Position", "Velocity"});
    auto current = list.begin();

    while(current != list.end()) {
        engine::Entity* entity = *current;


        // entity->alive = false;
        current++;
    }
}

void drawObjects() {
    auto list = world->subset({"Position", "RenderRectangle"});
    auto current = list.begin();

    while(current != list.end()) {
        engine::Entity* entity = *current;

        Position position               = (Position) entity->components.find("Position");
        RenderRectangle renderRectangle = (RenderRectangle) entity->components.find("RenderRectangle");
        current++;
    }
}

void display() {
    world->update();

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
        glColor3f(1, 0, 0);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    world->registerSystem(&drawObjects);

    glutInit(&argc, argv);
    glutInitWindowSize(1000, 1000);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Arpg game");
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
