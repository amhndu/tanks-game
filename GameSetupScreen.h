#ifndef GAMESETUPSCREEN_H
#define GAMESETUPSCREEN_H

#include "AppState.h"
#include "Menu.h"

#include <string>
#include <array>

class GameSetupScreen : public AppState
{
    public:
        GameSetupScreen();
        virtual ~GameSetupScreen() = default;
        void reset();
        void draw(sf::RenderWindow &window);
        void update(float dt);
        void passEvent(sf::Event event);
    private:
        Menu setupMenu;
        Menu numPlayersSubMenu;
        Menu landTypeSubMenu;
        int numOfPlyrs;
        int l_type;
        sf::Sprite bg;
        std::array<std::string,4> landtypes{{"Flats","Valley","Hilly","Random"}};
};

#endif // GAMESETUPSCREEN_H
