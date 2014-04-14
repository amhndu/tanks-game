#ifndef WORLDTEXT_H
#define WORLDTEXT_H
#include "WorldObject.h"

class WorldText : public WorldObject
{
    public:
        WorldText();
        WorldText(std::function<void(WorldText&,float)> m);
        WorldText(std::function<void(WorldText&,float)> m,sf::Text &t);
        void setString(std::string str){ text.setString(str); }
        sf::Text& getText(){ return text; }
        void setModifier(std::function<void(WorldText&,float)> modder);
        void handleCollision(WorldObject &b);
        void draw(sf::RenderTarget &target);
        void step(float dt);
        void reset();
    private:
        sf::Text text;
        std::function<void(WorldText&,float)> modifier;
};

#endif // WORLDTEXT_H
