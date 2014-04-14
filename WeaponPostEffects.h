#ifndef WEAPONPOSTEFFECTS_H
#define WEAPONPOSTEFFECTS_H
#include "WorldObject.h"
#include "Animation.h"
//Effects seen after a weapon explodes ...
class Tank;
class Explosion : public WorldObject
{
    public:
        Explosion(AnimationType animType,sf::Vector2f pos,int r = 25);
        ~Explosion();
        inline void setRadius(int r){ expCircle.setRadius(r); }
        inline int getRadius(){ return expCircle.getRadius(); }
        void handleCollision(WorldObject &b);
        void draw(sf::RenderTarget &target);
        void step(float dt);
        void reset();
    private:
        std::map<Tank*,bool> tanksActedOn;
        sf::CircleShape expCircle;
        std::unique_ptr<Animation> expAnim;
};

#endif // WEAPONPOSTEFFECTS_H
