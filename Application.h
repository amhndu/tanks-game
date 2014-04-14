#ifndef APPLICATION_H
#define APPLICATION_H
#include <deque>
#include <string>
#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "MessageStream.h"
#include "Game.h"
#include "GameOverScreen.h"

class Application
{
public:
    Application() = delete;
    static sf::RenderWindow& getWindow(){ return mainWindow;  }
    static sf::Texture& getTexture(TextureIdentifier id);
    static sf::Font& getFont(FontIdentifier id);
    static AppStateType getCurrentStateType() { return statesStack.back(); }
    static void changeState(AppStateType as);
    static MessageStream& getMsgStream() { return msgStream; }
    static void loadResources();
    static void run();
    static Game& getGame(){ return mGame; }
private:
    static AppState* getState(AppStateType as);
    static TextureManager textureMgr;
    static FontManager fontMgr;
    static bool ResourcesLoaded;
    static MessageStream msgStream;
    static std::deque<AppStateType> statesStack;
    static sf::RenderWindow mainWindow;
    static Game mGame;
    static GameOverScreen mGameOver;
    static AppState* currentState;
};

#endif // APPLICATION_H
