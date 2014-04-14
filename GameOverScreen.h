#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H
#include "AppState.h"

class GameOverScreen : public AppState
{
    public:
        GameOverScreen();
        void reset();
        void draw(sf::RenderWindow &window);
        void update(float dt);
        void receiveMessage(const Message& msg);
        void passEvent(sf::Event Event);
    private:
        sf::Texture bgImg;
        sf::Sprite bgSpr;
        sf::Text message;
        sf::Text gameOverText;
};

#endif // GAMEOVERSCREEN_H
