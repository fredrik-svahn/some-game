#include "headers.h"

using namespace ECS;
class WorldHandler {
public:
    std::string currentWorld;
    std::unordered_map<std::string, World*> worlds;

    void registerWorld(std::string name, World* world) {
        if(currentWorld == "") {
            setWorld(name);
        }

        worlds.insert({
            name,
            world
        });
    }

    void setWorld(std::string name) {
        currentWorld = name;
    }

    World* getCurrent() {
        return worlds.at(currentWorld);
    }
};
