#include "Application.h"
#include "ResourceIdentifiers.h"
void Application::run()
{
    mainWindow.create(sf::VideoMode(constants::windowWidth,constants::windowHeight),"A Game feat. Tanks");
    mainWindow.setFramerateLimit(120);
    sf::Clock frameTimer;
    changeState(TitleScreenState);
    msgStream.getGroup("AllAppStates").subscribe(&mGame);
    msgStream.getGroup("AllAppStates").subscribe(&mGameOver);
    msgStream.getGroup("GameState").subscribe(&mGame);
    currentState->reset();
    while(mainWindow.isOpen())
    {
        sf::Event event;
        while(mainWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                //msgStream.sendMessage(Message("WindowClosed"),"EventListeners");
                mainWindow.close();
                return;
            }
            else
                currentState->passEvent(event);
        }
        mainWindow.clear(sf::Color::White);
        currentState->draw(mainWindow);
        mainWindow.display();
        sf::Time dt = frameTimer.getElapsedTime();
        frameTimer.restart();
        currentState->update(dt.asSeconds());
    }
}
sf::Texture& Application::getTexture(TextureIdentifier id)
{
    if(!ResourcesLoaded)
        loadResources();
    return textureMgr.get(id);
}
sf::Font& Application::getFont(FontIdentifier id)
{
    if(!ResourcesLoaded)
        loadResources();
    return fontMgr.get(id);
}
void Application::loadResources()
{
    if(ResourcesLoaded)
        return;
    if( !(textureMgr.load(TankTexture,"data/tank.png") &&
    textureMgr.load(TurretTexture,"data/turret.png") &&
    textureMgr.load(ExplosionA,"data/ExplosionAsmall.png") &&
    textureMgr.load(TurretTarget,"data/target.png") &&
//    textureMgr.load(ExplosionB,"data/ExplosionB.png") &&
    textureMgr.load(ArrowDownSpriteSheet,"data/arrowdown.png") &&
    textureMgr.load(TitleBg,"data/title.png") &&
    fontMgr.load(Sensation,"data/sansation.ttf") &&
    fontMgr.load(UbuntuCondensed,"data/Ubuntu-C.ttf")) )
        throw std::runtime_error("failed to load resources");
    else
        ResourcesLoaded = true;
}
void Application::changeState(AppStateType as)
{
    statesStack.push_back(as);
    msgStream.getGroup("EventListeners").unsubscribe(currentState);
    currentState = getState(as);
    currentState->reset();
    msgStream.getGroup("EventListeners").subscribe(currentState);
}
AppState* Application::getState(AppStateType as)
{
    switch(as)
    {
    case TitleScreenState:
        return &titleState;
    case GameState:
        return &mGame;
    case GameOverState:
        return &mGameOver;
    }
    return nullptr;
}

TextureManager Application::textureMgr;
FontManager Application::fontMgr;
bool Application::ResourcesLoaded{false};
MessageStream Application::msgStream;
std::deque<AppStateType> Application::statesStack;
sf::RenderWindow Application::mainWindow;
Game Application::mGame;
GameOverScreen Application::mGameOver;
TitleScreen Application::titleState;
AppState* Application::currentState;
int main()
{
    srand(time(NULL));
    Application::loadResources();
    Application::run();
    return EXIT_SUCCESS;
}
