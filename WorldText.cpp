#include "WorldText.h"
#include "Application.h"

WorldText::WorldText() :
    WorldObject(PassiveType),
    text("",Application::getFont(Sensation),20),
    modifier([](WorldText& w,float t){return;})
{
    text.setColor(sf::Color::Black);
}
WorldText::WorldText(std::function<void(WorldText&,float)> m) :
    WorldObject(PassiveType),
    text("",Application::getFont(Sensation),20),
    modifier(m)
{
    text.setColor(sf::Color::Black);
}
WorldText::WorldText(std::function<void(WorldText&,float)> m,sf::Text &t) :
    WorldObject(PassiveType),
    text(t),
    modifier(m)
{
    text.setColor(sf::Color::Black);
}
void WorldText::setModifier(std::function<void(WorldText&,float)> modder)
{
    modifier = (modder);
}
void WorldText::handleCollision(WorldObject &b){ return; }
void WorldText::draw(sf::RenderTarget &target)
{
    std::string c = text.getString();
    target.draw(text);
}
void WorldText::step(float dt)
{
    modifier(*this,dt);
}
void WorldText::reset(){}
