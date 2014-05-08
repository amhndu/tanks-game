#include "GameSetupScreen.h"
#include "Application.h"
#include "Land.h"
GameSetupScreen::GameSetupScreen()  :
    AppState(GameSetupState),
    setupMenu(Application::getFont(FreeSans),40),
    numPlayersSubMenu(Application::getFont(FreeSans),40),
    landTypeSubMenu(Application::getFont(FreeSans),40),
    numOfPlyrs(2),
    l_type(Land::Flats),
    bg(Application::getTexture(TitleBg))
{
    setupMenu.setSelectionBgColor(sf::Color(0,0,0,100));
    setupMenu.setBackgroundColor(sf::Color::Transparent);
    setupMenu.setPosition(0,300);
    numPlayersSubMenu.setActive(false);
    numPlayersSubMenu.add(sf::Color::White," 2"," 3"," 4"," 5"," 6"," 7"," 8");
    numPlayersSubMenu.setBackgroundColor(sf::Color(100,100,100,150));
    numPlayersSubMenu.setSelectionBgColor(sf::Color(0,0,0,100));
    numPlayersSubMenu.create(200,4*numPlayersSubMenu.getLineSpacing());
    numPlayersSubMenu.setPosition(setupMenu.getPosition().x+constants::windowWidth/2,setupMenu.getPosition().y);
    landTypeSubMenu.setActive(false);
    landTypeSubMenu.setPosition(setupMenu.getPosition().x+constants::windowWidth/2,setupMenu.getPosition().y+setupMenu.getLineSpacing());
    landTypeSubMenu.add(sf::Color::White,"Flats","Valley","Hilly","Random");
    landTypeSubMenu.setBackgroundColor(sf::Color(100,100,100,150));
    landTypeSubMenu.setSelectionBgColor(sf::Color(0,0,0,100));
    landTypeSubMenu.create(200);
    setupMenu.add(sf::Color::White,"Players : "+std::to_string(numOfPlyrs),"Land type : "+landtypes[l_type],std::string("Start Game"));
    setupMenu.create(constants::windowWidth,constants::windowHeight);
}
void GameSetupScreen::reset(){}
void GameSetupScreen::draw(sf::RenderWindow &window)
{
    window.draw(bg);
    setupMenu.draw(window);
    if(numPlayersSubMenu.getActive())
        numPlayersSubMenu.draw(window);
    if(landTypeSubMenu.getActive())
        landTypeSubMenu.draw(window);
}
void GameSetupScreen::update(float dt)
{
    setupMenu.step(dt);
    numPlayersSubMenu.step(dt);
    landTypeSubMenu.step(dt);
    int query = setupMenu.querySelecion();
    if(query >= 0)
    {
        switch(query)
        {
        case 0://"Player"
            numPlayersSubMenu.setActive(true);
            landTypeSubMenu.setActive(false);
            setupMenu.setActive(false);
            break;
        case 1://"Land Type"
            landTypeSubMenu.setActive(true);
            numPlayersSubMenu.setActive(false);
            setupMenu.setActive(false);
            break;
        case 2://"Start Game"
            Application::changeState(GameState);
            Application::getGame().newGame(numOfPlyrs,static_cast<Land::Landtype>(l_type));
            break;
        default:
            assert(false);
        }
    }
    if(numPlayersSubMenu.getActive())
    {
        query = numPlayersSubMenu.querySelecion();
        if(query >= 0)
        {
            numOfPlyrs = query+2;
            numPlayersSubMenu.setActive(false);
            setupMenu.setActive(true);
            setupMenu.clear();
            setupMenu.add(sf::Color::White,"Players : "+std::to_string(numOfPlyrs),"Land type : "+landtypes[l_type],"Start Game");
            setupMenu.create(constants::windowWidth,0);
        }
    }
    else if(landTypeSubMenu.getActive())
    {
        query = landTypeSubMenu.querySelecion();
        if(query >= 0)
        {
            l_type = query;
            landTypeSubMenu.setActive(false);
            setupMenu.clear();
            setupMenu.setActive(true);
            setupMenu.add(sf::Color::White,"Players : "+std::to_string(numOfPlyrs),"Land type : "+landtypes[l_type],"Start Game");
            setupMenu.create(constants::windowWidth,0);
        }
    }
}
void GameSetupScreen::passEvent(sf::Event event)
{
    setupMenu.passEvent(event);
    landTypeSubMenu.passEvent(event);
    numPlayersSubMenu.passEvent(event);
}
