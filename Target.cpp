#include "Target.h"
#include "Application.h"

Target::Target(Player &pl):
    targetSpr(Application::getTexture(TurretTarget)),
    playr(pl)
{
    targetSpr.setOrigin(-50,0); // padding = 50
}
void Target::draw(sf::RenderTarget &target)
{
    target.draw(targetSpr);
}
void Target::step(float dt)
{
    targetSpr.setPosition(playr.getTankPos());
    targetSpr.setRotation(playr.getTurretAngle());
}
void Target::receiveMessage(const Message& msg)
{
    if(msg.ID == "Self Destruct")
        selfDestruct = true;
}
