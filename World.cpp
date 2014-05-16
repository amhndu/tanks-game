#include "World.h"
#include "Tank.h"
#include "Land.h"
#include <iostream>

World::World() : timer(0) { }
//WorldObject* World::addObj(WorldObjectptr obj)
//{
//    objects.push_back(std::move(obj));
//    return objects.back().get();
//}
WorldObject* World::addObj(WorldObject* optr)
{
    objects.push_back(WorldObjectptr(optr));
    return optr;
}
WorldObject* World::addObj(WorldObject::Type t)
{
    WorldObjectptr obj;
    bool playNice = true;
    switch(t)
    {
    case WorldObject::TankType:
        obj.reset(new Tank());
        break;
    case WorldObject::LandType:
        obj.reset(new Land());
        break;
    default:
        playNice = false;
    }
    if(playNice)
    {
        objects.push_back(std::move(obj));
        return objects.back().get();
    }
    return nullptr;
}
void World::removeObj(std::list<WorldObjectptr>::iterator o)
{
    objects.erase(o);
}
void World::drawAll(sf::RenderWindow &win)
{
    for(auto &objit : objects)
        objit->draw(win);
}
void World::crudeStepAll(float dt)
{
    for(auto objit = objects.begin();objit != objects.end();)
    {
        if(!((*objit)->selfDestruct))
        {
            for(auto j = std::next(objit) ; j != objects.end() ; ++j)
                (*objit)->handleCollision(*(*j).get());
            /*                             ^
            dereference the iterator , get the raw pointer and dereference it*/
            (*objit)->step(dt);
            ++objit;
        }
        else
            objit = objects.erase(objit);
    }
}
void World::stepAll(float dt)
{
//    crudeStepAll(dt);
    timer += dt;
    while(timer > updateRate)
    {
        timer -= updateRate;
        crudeStepAll(updateRate);
    }
}
void World::play()
{
    for(auto &objit : objects)
        objit->reset();
    timer = 0;
}
void World::traceAll()
{
    int i = 1;
    for(auto obj = objects.begin() ; obj != objects.end() ; ++obj,++i)
    {
        std::cout << "Object " << i << std::endl;
        std::cout << "\tobject.type = " << (*obj)->type << std::endl;
        std::cout << "\tobject.selfDestruct = " << (*obj)->selfDestruct << std::endl;
        std::cout << "\tAddress of object = " << (*obj).get() << std::endl;
    }
}
