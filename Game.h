#ifndef GAME_H
#define GAME_H
#include "World.h"
#include "Land.h"
#include "Player.h"
#include "AppState.h"

class Game : public AppState
{
public:
    Game();
    void draw(sf::RenderWindow &window);
    void update(float dt);
    void receiveMessage(const Message &msg);
    void passEvent(sf::Event Event);
    void reset();

    sf::Vector2f getLandNormal(int x,int y){ return land->getNormal(x,y); }
    float getLandNormAng(int x,int y){ return land->getNormAngle(x,y); }
    int getLandHeight(int x){ return land->getHeight(x); }

    WorldObject* addWorldObj(WorldObject* wo){ return world.addObj(wo); }

    size_t getPlayerIndex(){ return playerActive; }
    Player* getCurrPlayer(){ return players[playerActive].get(); }
    bool isPlayerTurn(){ return counter==0 && landSliding==false; }
private:
    std::deque<Playerptr> players;
    size_t playerActive;

    //flags and counters
    int counter; //weapons,effects,tanks on free fall etc. counter
    bool landSliding;

    Land *land;
    World world;
private:
    void handleInput();

};

#endif // GAME_H
