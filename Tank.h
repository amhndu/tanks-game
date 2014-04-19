#ifndef Tank_H
#define Tank_H

#include "WorldObject.h"
class Player;
class Tank : public WorldObject
{
public:
    Tank();
    ~Tank();
    void draw(sf::RenderTarget &target);
    void step(float dt);
    void handleCollision(WorldObject &b);
    void reset();
    void receiveMessage(const Message& msg);

    void setMovement(int val);
    void weapAct(float ); //called when hit by some weapon
    void setPosition(const sf::Vector2f& pos);
    void setPosition(int x,int y) { setPosition(sf::Vector2f(x,y)); }
    friend class Player;
    void setPlayer(Player *p);
    Player &getPlayer() { return *myOwner;  }

    sf::Sprite& getTankSpr(){ return tank; }
    sf::Sprite& getTurretSpr(){ return turret; }
    sf::RectangleShape getTankRect();

private:
    void setLifeFill(int l);

    Player *myOwner;
    int moving;//on land
    sf::Sprite tank;
    sf::Sprite turret;
    sf::RectangleShape lifeBg;
    sf::RectangleShape lifeFill;
    bool freefall;
    sf::Vector2f velocity;
};

#endif // Tank_H
