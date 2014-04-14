#include "GameOverScreen.h"
#include "Application.h"

GameOverScreen::GameOverScreen() :
    AppState(GameOverState),
    bgImg(),
    bgSpr(),
    message("",Application::getFont(Sensation)),
    gameOverText("Game Over !",Application::getFont(Sensation))
{
    message.setColor(sf::Color::Black);
    gameOverText.setColor(sf::Color::Black);
    gameOverText.setCharacterSize(40);
    message.setCharacterSize(20);
    gameOverText.setOrigin(gameOverText.getLocalBounds().width/2,gameOverText.getLocalBounds().height/2);
}
void GameOverScreen::reset()
{
    sf::RenderWindow &win = Application::getWindow();
    bgImg.create(win.getSize().x,win.getSize().y);
    bgImg.update(win);
    bgSpr.setTexture(bgImg);
    gameOverText.setPosition(win.getSize().x/2,2*gameOverText.getCharacterSize());
    message.setOrigin(message.getLocalBounds().width/2,message.getLocalBounds().height/2);
    message.setPosition(gameOverText.getPosition().x,gameOverText.getPosition().y
                        + gameOverText.getLocalBounds().height + message.getCharacterSize());
}
void GameOverScreen::draw(sf::RenderWindow &window)
{
    window.draw(bgSpr);
    window.draw(gameOverText);
    window.draw(message);
}
void GameOverScreen::update(float dt){}
void GameOverScreen::passEvent(sf::Event Event)
{
    if(Event.type == sf::Event::KeyPressed || Event.type == sf::Event::MouseButtonReleased)
        Application::changeState(GameState);
}
void GameOverScreen::receiveMessage(const Message& msg)
{
    if(msg.ID == "GameOver")
    {
        const std::string &gcase = msg.getItem<std::string>(0);
        message.setString(gcase);
        reset();
    }
}
