/*
	No rights Reserved.
	Amish Kumar Naidu
	amhndu at gmail.com
*/
#include "Missile.h"
#include "Application.h"
#include "Land.h"
#include "Tank.h"
#include "utilities.h"
#include "WeaponPostEffects.h"

Missile::Missile(double x, double y) : velocity(0, 0) , acceleration(0, constants::gravity)
{
    type = WorldObject::WeaponType;
    selfDestruct = false;
    projectile.setRadius(2.5);
    projectile.setFillColor(sf::Color::Magenta);
    projectile.setPosition(x, y);
    Application::getMsgStream().sendMessage(Message("WeapObjCreated"),"GameState");
}
Missile::~Missile()
{
    Application::getMsgStream().sendMessage(Message("WeapObjDestroyed"),"GameState");
}
void Missile::setVelocity(double x, double y)
{
    velocity.x = x;
    velocity.y = y;
}
void Missile::setAcceleration(double x, double y)
{
    acceleration.x = x;
    acceleration.y = y;
}
void Missile::handleCollision(WorldObject &b)
{
    switch(b.type)
    {
    case WorldObject::TankType:
    {
        Tank &t = static_cast<Tank&>(b);
        if(intersects(projectile,t.getTankRect()))
            explode();
    }
    break;
    case WorldObject::LandType:
    {
        Land &l = static_cast<Land&>(b);
        if(projectile.getPosition().y + projectile.getRadius() > (constants::windowHeight - l.getHeight(projectile.getPosition().x)))
            explode();
    }
    break;
    default:
        break;
    }
}
void Missile::draw(sf::RenderTarget &target)
{
    target.draw(projectile);
}
void Missile::step(float dt)
{
    velocity += acceleration * dt;
    projectile.move( velocity * dt );
    if(projectile.getPosition().x >= constants::windowWidth || projectile.getPosition().x < 0
       || projectile.getPosition().y >= constants::windowHeight)
    {
        selfDestruct = true;
    }
}
void Missile::explode()
{
    Application::getMsgStream().sendMessage(Message("DestroyCircle",sf::Vector2i(projectile.getPosition()),30),"Land");
    Application::getGame().addWorldObj(new Explosion(MissileExplosionA,projectile.getPosition(),30));
    selfDestruct = true;
}
