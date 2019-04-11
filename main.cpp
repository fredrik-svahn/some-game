#define STB_IMAGE_IMPLEMENTATION
#define FPS 60

#include "headers.h"
#include "WorldHandler.h"
#include "systems.h"

using namespace ECS;

WorldHandler* handler = new WorldHandler();

int load(const char* file) {
    unsigned int texture;
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}

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
    int playersprite = load("./assets/player.png");

    World* world = World::createWorld();
    handler->registerWorld("game", world);

    world->registerSystem(new MovementSystem());
    world->registerSystem(new SpriteSystem());

    Entity* e = world->create();
    e->assign<Sprite>(40,40);
    e->assign<Color>(1,0.2,0);
    e->assign<Velocity>(0,0);
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

class ChangeWorldSubscriber : public EventSubscriber<ChangeWorldEvent> {
public:
    virtual ~ChangeWorldSubscriber() {}

    virtual void receive(World* world, const ChangeWorldEvent& event) {
        handler->currentWorld = event.world;
    }
};
