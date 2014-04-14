#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H
#include <SFML/Graphics.hpp>
#include <memory>
#include "MsgComponents.h"

class WorldObject;
typedef std::unique_ptr<WorldObject> WorldObjectptr;

class WorldObject : public Receiver
{
public:
    enum Type
    {
        PassiveType ,
        LandType,
        TankType,
        WeaponType,
        WeaponPostEffectType,
        TotalTypes
    } type;
    WorldObject() = default;
    WorldObject(Type m_type) : type(m_type) , selfDestruct(false) {}
    virtual ~WorldObject(){};
    virtual void handleCollision(WorldObject &b) = 0;
    virtual void draw(sf::RenderTarget &target) = 0;
    virtual void step(float dt) = 0;
    virtual void reset() = 0;
    bool selfDestruct; //if true, World deletes the object
};

#endif // WORLDOBJECT_H
