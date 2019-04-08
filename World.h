#include <vector>
#include <iostream>
#include <unistd.h>
#include <string>
#include <unordered_map>
#include <functional>

#define ComponentBag std::unordered_map<std::string, engine::Component>


namespace engine {

    struct Component {};

    struct Entity {
        bool alive = true;
        ComponentBag components;
    };


    class World {
    public:
        void spawn(ComponentBag bag) {
            Entity* entity = new Entity();
            entity->components = bag;
            entity->alive = true;

            entities.push_back(entity);
        }

        void spawn_v(std::vector<std::pair<std::string, Component>> init_list) {
            ComponentBag bag;

            for(std::pair<std::string, Component> pair : init_list) {bag.insert(pair); }
            spawn(bag);
        }

        std::vector<Entity*> subset(std::vector<std::string> required_components) {
            std::vector<Entity*> result;

            for(auto entity : entities) {
                bool contains_all = true;

                for(auto component_name : required_components) {
                    if(!entity->components.count(component_name)) {
                        contains_all = false;
                        break;
                    }
                }

                if(contains_all) result.push_back(entity);
            }
            return result;
        }

        void registerSystem(std::function<void(void)> system) {
            systems.push_back(system);
        }

        void clean() {
            int i = 0;
            int x = 0;
            while(i < entities.size()) {
                Entity* entity = entities[i];

                if(!entity->alive) {
                    delete entity;
                    entities.erase(entities.begin() + i);
                }
                else {
                    i++;
                }
                x++;
            }
        }

        void update() {
            for(auto system: systems) {
                system();
            }

            clean();
        }

    private:
        std::vector<Entity*> entities;
        std::vector<std::function<void(void)>> systems;
    };
}
