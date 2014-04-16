/*
	No rights Reserved.
	Amish Kumar Naidu
	amhndu at gmail.com
*/
#include "Application.h"
#include "constants.h"
#include "WorldText.h"
#include "CtrlPanel.h"
#include <cassert>

//#define STEPPED
Game::Game() : AppState(GameState),counter(0) {}
void Game::reset()
{
    world.clear();
    players.clear();
    counter = 0;

    land = static_cast<Land*>(world.addObj(WorldObject::LandType));
    auto &gland = Application::getMsgStream().getGroup("Land");
    gland.clear();
    gland.subscribe(land);
    land->genHeightMap(Land::Random);
    playerActive = 0;

    auto &gCtrlPanel = Application::getMsgStream().getGroup("CtrlPanel");
    gCtrlPanel.clear();
    gCtrlPanel.subscribe(world.addObj(new CtrlPanel(*this)));

    auto &gtanks = Application::getMsgStream().getGroup("Tanks");
    gtanks.clear();
    //initialize players
    int p = 2;
    int pw = constants::windowWidth/p; //divide width into p parts
    for(int i = 0;i < p; ++i)
    {
        Tank* pTank = static_cast<Tank*>(world.addObj(WorldObject::TankType));
        gtanks.subscribe(pTank);
        Playerptr pl(new Player(pTank));
        int x = rand()%(pw-50) + pw*i + 25; //place tank within the ith part within a padding of 25pixels on both sides
        pTank->setPosition(sf::Vector2f(x,constants::windowHeight-getLandHeight(x)-10));
        pTank->setPlayer(pl.get());
        players.push_back(std::move(pl));
    }
    world.play();
}

void Game::draw(sf::RenderWindow &window)
{
    world.drawAll(window);
}
void Game::update(float dt)
{
    if(isPlayerTurn()) //i.e weapObjs == 0 && landSliding == false
    {   //check if game is over
        if(players.size() == 1)
        {
            Application::getMsgStream().sendMessage(Message("GameOver",
                                                            std::string("Last Tank Alive Won")),"AllAppStates");
            Application::changeState(GameOverState);
            reset();
        }
        else if(players.size() == 0)
        {
            Application::getMsgStream().sendMessage(Message("GameOver",
                                                            std::string("Game Drawn")),"AllAppStates");
            Application::changeState(GameOverState);
            reset();
        }
    }
    #ifndef STEPPED
    world.stepAll(dt);
    #endif // STEPPED
}
void Game::passEvent(sf::Event Event)
{
    if(Event.type == sf::Event::KeyPressed)
    {
        switch(Event.key.code)
        {
        case sf::Keyboard::C:
            reset();
            break;
        case sf::Keyboard::H:
            land->genHeightMap(Land::Hilly);
            break;
        case sf::Keyboard::F:
            land->genHeightMap(Land::Flats);
            break;
        case sf::Keyboard::V:
            land->genHeightMap(Land::Valley);
            break;
        case sf::Keyboard::Left:
            if( isPlayerTurn() && players[playerActive] != nullptr)
                players[playerActive]->moveTank(-1);
            break;
        case sf::Keyboard::Right:
            if( isPlayerTurn() && players[playerActive] != nullptr)
                players[playerActive]->moveTank(1);
            break;
#ifdef STEPPED
        case sf::Keyboard::S:
            world.crudeStepAll();
            break;
#endif // STEPPED
        default:
            break;
        }
    }
//    if( isPlayerTurn() && players[playerActive] != nullptr)
//        players[playerActive]->handleInput(Event);
    Application::getMsgStream().sendMessage(Message("WindowEvent",Event),"CtrlPanel");
}
void Game::receiveMessage(const Message& msg)
{
    if(msg.ID == "SetLandSlide")
    {
        landSliding = true;
    }
    else if(msg.ID == "UnsetLandSlide")
    {
        landSliding = false;
    }
    else if(msg.ID == "PlayerTurnOver")
    {
        if(++playerActive >= players.size())
                playerActive = 0;
    }
    else if(msg.ID == "TankDestroyed")
    {
        size_t pi = 0;
        for(auto p_it = players.begin();p_it != players.end();)
        {
            if((*p_it)->isDead())
            {
                Application::getMsgStream().getGroup("Tanks").unsubscribe(&(*p_it)->getTank());
                p_it = players.erase(p_it);
                if(pi < playerActive) --playerActive;
            }
            else    (++p_it,++pi);
        }
    }
}
