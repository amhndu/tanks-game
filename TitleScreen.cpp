#include "TitleScreen.h"
#include "Application.h"

TitleScreen::TitleScreen()  :
    AppState(TitleScreenState),
    bg(Application::getTexture(TitleBg)),
    mainMenu(Application::getFont(FreeMono),40)
{
    mainMenu.add("Play",sf::Color::White);
    mainMenu.add("Exit",sf::Color::White);
    mainMenu.setSelectionBgColor(sf::Color(100,100,100,50));
    mainMenu.setScrollBarColor(sf::Color(200,200,200));
    mainMenu.create(0,0);
    mainMenu.setPosition(0,300);
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
    mainMenu.draw(window);
}
void TitleScreen::update(float dt)
{
    mainMenu.step(dt);
    int query = mainMenu.querySelecion();
    if(query >= 0)
    {
        switch(query)
        {
        case 0://Play
            Application::changeState(GameState);
            Application::getGame().reset();
            break;
        case 1:
            Application::quit();
            break;
        default:
            PRINT_VAR(query)
            break;
        }
    }
}
void TitleScreen::passEvent(sf::Event event)
{
    mainMenu.passEvent(event);
}
