#include "./include/ECS.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "components.h"

#define _USE_MATH_DEFINES

#include <math.h>

using namespace ECS;

#define _USE_MATH_DEFINES

#define E ComponentHandle

class MovementSystem : public EntitySystem {
public:
    virtual void tick(World* world, float deltaTime) override {
        world->each<Position, Velocity>(
            [&](
                Entity* ent,
                E<Position> position,
                E<Velocity> velocity
            ) {
            position->x += velocity->x * deltaTime / 1000;
            position->y += velocity->y * deltaTime / 1000;
            position->z += velocity->z * deltaTime / 1000;
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

                glMatrixMode(GL_PROJECTION);
                glPushMatrix();
                glLoadIdentity();

                glScalef(sprite->w/w, sprite->h/h, 1);
                glTranslatef(position->x, position->y, position->z);
                glBegin(GL_QUADS);
                    glColor3f(color->r, color->g, color->b);
                    glVertex3f(-1, 1, 0);
                    glVertex3f(1, 1, 0);
                    glVertex3f(1, -1, 0);
                    glVertex3f(-1, -1, 0);
                glEnd();
                glPopMatrix();
        });
    }
};
