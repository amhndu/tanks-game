#ifndef MISSILE_H
#define MISSILE_H
#include "WorldObject.h"

class Missile : public WorldObject
{
public:
    Missile(double x, double y);
    ~Missile();
    void handleCollision(WorldObject &b);
    void draw(sf::RenderTarget &target);
    void step(float dt);
    void setVelocity(double x, double y);
    void setAcceleration(double x, double y);
    inline void reset(){    selfDestruct = true;    }
private:
    void explode(void);
    sf::CircleShape projectile;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
};

#endif // MISSILE_H
