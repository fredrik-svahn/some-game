#define _USE_MATH_DEFINES
#define E ComponentHandle


#include "headers.h"
#include "components.h"
#include <math.h>

using namespace ECS;

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
                glTranslatef(position->x, position->y, 0);

                glMatrixMode(GL_MODELVIEW);
                glBegin(GL_QUADS);
                    glColor3f(color->r, color->g, color->b);
                    glVertex2f(-1, 1);
                    glVertex2f(1, 1);
                    glVertex2f(1, -1);
                    glVertex2f(-1, -1);
                glEnd();
                glPopMatrix();
        });
    }
};
