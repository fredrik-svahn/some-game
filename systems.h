#include "./include/ECS.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

using namespace ECS;

#define E ComponentHandle
#define TICK "virtual void tick(World* world, float deltaTime) override"
struct Position {
    Position(double x, double y): x(x), y(y) {}
    double x;
    double y;
};

struct Velocity {
    Velocity(double x, double y): x(x), y(y) {}
    double x;
    double y;
};

struct Color {
    Color(double r, double g, double b): r(r), g(g), b(b) {}
    double r;
    double g;
    double b;
};

struct Sprite {
    Sprite(double w, double h): w(w), h(h) {}
    double w;
    double h;
};


class MovementSystem : public EntitySystem {
public:
    virtual void tick(World* world, float deltaTime) override {
        world->each<Position, Velocity>([&](Entity* ent, E<Position> position, E<Velocity> velocity) {
            position->x += velocity->x * deltaTime;
            position->y += velocity->y * deltaTime;
        });
    }
};

class SpriteSystem : public EntitySystem {
public:
    virtual void tick(World* world, float deltaTime) override {
        world->each<Position, Sprite, Color>(
            [&](
                Entity* ent,
                E<Position> position,
                E<Sprite> sprite,
                E<Color> color
            ) {
                double w = glutGet(GLUT_WINDOW_WIDTH);
                double h = glutGet(GLUT_WINDOW_HEIGHT);

                double x1 = position->x - w/2;
                double y1 = position->y - h/2;

                double x2 = x1 + sprite->w;
                double y2 = y1 + sprite->h;

                x1 /= w/2;
                x2 /= w/2;
                y1 /= h/2;
                y2 /= h/2;

                glBegin(GL_QUADS);
                    glColor3f(color->r, color->g, color->b);
                    glVertex2f(x1, y1);
                    glVertex2f(x2, y1);
                    glVertex2f(x2, y2);
                    glVertex2f(x1, y2);
                glEnd();
        });
    }
};
