#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>

class Menu
{
public:
    Menu(const sf::Font &f,int charSize = 20,int linePad = 4,int scrollBarWidth = 6);
    ~Menu() = default;
    void draw(sf::RenderTarget &target);
    template<typename... Tail>
    void add(const std::string& str,Tail... T)
    {
        add(str);
        add(T...);
    }
    //the string mustn't contain any escape characters like '\n' and '\v' i.e they should only
    //span one line
    void add(const std::string& item,sf::Color textColor = sf::Color::Black);
    void step(float dt);
    //create the menu after adding all the menu item
    //calling with no arguments means set it to fit all the menu items,
    //width >= max width of menu items
    //height is rounded to a nearby multiple of (linePadding+characterSize), and the extra menu items are scrollable
    void create(float width = 0,float height = 0);
    void passEvent(const sf::Event& event);
    int getCharacterSize(){ return characterSize; }
    int getLinePadding(){ return linePadding; }
    void setCharacterSize(int size){ characterSize=size;}
    void setLinePadding(int pad){ linePadding=pad;}
    void setPosition(float x,float y)
    {
        scrollBar.move(-spr.getPosition());
        spr.setPosition(x,y);
        scrollBar.move(spr.getPosition());
    }
    sf::Vector2f getPosition(){ return spr.getPosition();}
private:
    void updateTexture(int deltaScroll = 0);
    sf::RenderTexture rndrTxtre;
    sf::Sprite spr;
    sf::RectangleShape selectionBg;
    sf::RectangleShape scrollBar;
    sf::View view;
    const sf::Font &font;
    std::list<std::unique_ptr<sf::Text>> menuList;
    int characterSize;
    int linePadding;
    int marker;
    int itemsVisible; //in the view
    int scrolled;//no of items above not visible
    bool scroll;
};

#endif // MENU_H
