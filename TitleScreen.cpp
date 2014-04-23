#include "TitleScreen.h"
#include "Application.h"

TitleScreen::TitleScreen()  :
    AppState(TitleScreenState),
    bg(Application::getTexture(TitleBg)),
    mainMenu()
{
}

TitleScreen::~TitleScreen()
{
    //dtor
}
void TitleScreen::reset()
{}
void TitleScreen::draw(sf::RenderWindow &window)
{
    window.draw(bg);
}
void TitleScreen::update(float dt)
{}
void TitleScreen::passEvent(sf::Event event)
{
    if(event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseButtonReleased)
        Application::changeState(GameState);
}
