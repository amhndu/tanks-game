#ifndef TARGET_H
#define TARGET_H
#include "WorldObject.h"
#include "Player.h"

class Target : public WorldObject
{
    public:
        Target(Player& pl);
        ~Target() = default;
        void handleCollision(WorldObject &b) {};
        void draw(sf::RenderTarget &target);
        void step(float dt);
        void reset(){ selfDestruct = true;};
        void receiveMessage(const Message& msg);
    private:
        sf::Sprite targetSpr;
        Player& playr;
};

#endif // TARGET_H
