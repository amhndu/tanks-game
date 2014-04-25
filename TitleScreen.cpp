#include "TitleScreen.h"
#include "Application.h"

TitleScreen::TitleScreen()  :
    AppState(TitleScreenState),
    bg(Application::getTexture(TitleBg)),
    mainMenu(Application::getFont(FreeSans),40)
{
    mainMenu.add("Play",sf::Color::White);
    mainMenu.add("Exit",sf::Color::White);
    mainMenu.setSelectionBgColor(sf::Color(0,0,0,100));
    mainMenu.create(constants::windowWidth,0);
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
            Application::changeState(GameSetupState);
            break;
        case 1://Exit
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
