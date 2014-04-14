#ifndef CtrlPanel_H
#define CtrlPanel_H
#include "WorldObject.h"
#include "Game.h"

class CtrlPanel : public WorldObject
{
public:
    CtrlPanel(Game& g);
    void handleCollision(WorldObject &b){};
    void draw(sf::RenderTarget &target);
    void step(float dt);
    void reset(){};
    void receiveMessage(const Message& msg);
private:
    void initSettingAngle(Player *pl);
    void postSettingAngle();
    void changePower(int delta,Player *pl);
    Game& _game;
    int fpsi;
    size_t p;
    bool settingPower;
    bool settingAngle;    //if setting angle change angle of the turret by deltaX
    int prevMouseX;       //deltaX = mouse.x - prevMouseX , change angle in degrees
    sf::Vector2i mouseOldCoord;// used to reset mouse to old position after setting angle
    sf::Clock fpsTimer;
    sf::Text fps;
    sf::Text player;
    sf::Text rotation;
    sf::Text power;
    sf::Text fire;
    sf::RectangleShape gaugeBg;
    sf::RectangleShape gaugeFill;
};

#endif // CtrlPanel_H
