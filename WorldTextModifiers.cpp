#include "WorldTextModifiers.h"
#include "WorldText.h"
#include "Game.h"
#include <sstream>

std::unique_ptr<WorldText> WorldTextCreator::create(WTMIdentifier id)
{
    std::unique_ptr<WorldTextModifier> wtm(nullptr);
    std::unique_ptr<WorldText> wt(new WorldText);
    switch(id)
    {
    case MouseCoord:
        wtm.reset(new MouseCoordWTM());
        break;
    }
    wt->setModifier(std::move(wtm));
    return wt; //move
}

void MouseCoordWTM::init(WorldText &WT)
{
    WT.text.setPosition(30,30);
    WT.text.setColor(sf::Color::Black);
    WT.text.setCharacterSize(20);
}

void MouseCoordWTM::modify(WorldText &WT,float dt)
{
    sf::Vector2i mouse = sf::Mouse::getPosition(Game::getWindow());
    std::stringstream ss;
    ss << mouse.x << " , " << mouse.y;
    WT.text.setString(ss.str());
}
