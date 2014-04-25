#ifndef APPSTATE_H
#define APPSTATE_H
#include <memory>
#include <deque>
#include "MsgComponents.h"
#include <SFML/Graphics.hpp>

enum AppStateType
{
    TitleScreenState,
    GameSetupState,
    GameState,
    GameOverState
};

class AppState : public Receiver
{
    public:
        AppState();
        AppState(AppStateType t) : type(t) {};
        virtual ~AppState(){};
        virtual void reset() = 0;
        virtual void draw(sf::RenderWindow &window) = 0;
        virtual void update(float dt) = 0;
        virtual void passEvent(sf::Event event) = 0;
        AppStateType type;
};

#endif // APPSTATE_H
