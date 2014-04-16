#include "Target.h"
#include "Application.h"

Target::Target(Player &pl):
    targetSpr(Application::getTexture(TurretTarget)),
    playr(pl)
{}
void Target::draw(sf::RenderTarget &target)
{
    target.draw(targetSpr);
}
void Target::step(float dt)
{
    int padding = 50;
    float angle = TO_RAD(playr.getTurretAngle());
    sf::Vector2f tpos = playr.getTankPos();
    targetSpr.setPosition(tpos.x+padding*std::cos(angle),tpos.y+padding*std::sin(angle));
}
void Target::receiveMessage(const Message& msg)
{
    if(msg.ID == "Self Destruct")
        selfDestruct = true;
}
