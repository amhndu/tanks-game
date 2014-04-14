#ifndef WORLD_H
#define WORLD_H
#include <list>
#include "WorldObject.h"

class World
{
public:
    World();
    ~World() = default;
//    WorldObject* addObj(WorldObjectptr);
    WorldObject* addObj(WorldObject*);
    WorldObject* addObj(WorldObject::Type t);
    void removeObj(std::list<WorldObjectptr>::iterator);
    void play();
    void drawAll(sf::RenderWindow &win);
    void stepAll(float dt);
    void crudeStepAll(float dt);
    void traceAll();
    void clear(){ objects.clear(); }
    std::list<WorldObjectptr> objects;
private:
    float timer;
    const double updateRate{1.f/100.f}; //seconds per update
};

#endif // WORLD_H
