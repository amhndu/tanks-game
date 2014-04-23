#include "Menu.h"
#include "Application.h"
#include "utilities.h"

Menu::Menu(const sf::Font& f,int charSize,int linePad,int scrollBarWidth) :
    rndrTxtre(),
    spr(),
    selectionBg(),
    scrollBar(),
    view(),
    font(f),
    menuList(),
    characterSize(charSize),
    linePadding(linePad),
    marker(0),
    itemsVisible(0),
    scrolled(0),
    scroll(false)
{
    selectionBg.setFillColor(sf::Color(210,210,210));
    scrollBar.setFillColor(sf::Color(100,100,100));
    scrollBar.setSize(sf::Vector2f(scrollBarWidth,0));
}
void Menu::draw(sf::RenderTarget &target)
{
    target.draw(spr);
    if(scroll)
        target.draw(scrollBar);
}
void Menu::add(const std::string& item,sf::Color textColor)
{
    std::unique_ptr<sf::Text> newText(new sf::Text(item,font,characterSize));
    newText->setColor(textColor);
    newText->setPosition(0,menuList.size()*(linePadding+characterSize));
    menuList.push_back(std::move(newText));
}
void Menu::create(float width,float height)
{
    if(height == 0)
        height = menuList.size()*(linePadding+characterSize);
    else
        height = round(height,linePadding+characterSize);

    itemsVisible = height/(linePadding+characterSize);

    //max width of the sf::Texts of the menu items
    float maxwidth = (**std::max_element(menuList.begin(),menuList.end(),
                            [](sfTextPtr& a,sfTextPtr &b){ return a->getLocalBounds().width<b->getLocalBounds().width;})).getLocalBounds().width;
    if(itemsVisible != menuList.size())
    {
        scroll = true;
        maxwidth += scrollBar.getSize().x;
    }
    if(width == 0)  width = maxwidth;
    else
        width = std::max(width,maxwidth);
    rndrTxtre.create(width,height);
    view = rndrTxtre.getDefaultView();
    view.setSize(width,height);
    selectionBg.setSize(sf::Vector2f(width,linePadding+characterSize));
    if(scroll)
    {
        scrollBar.setSize(sf::Vector2f( scrollBar.getSize().x,std::max(5.0f,height/(menuList.size()+1-itemsVisible))));
        scrollBar.setPosition(width,0);
    }

    rndrTxtre.clear(sf::Color::Transparent);
    rndrTxtre.draw(selectionBg);
    for(const auto &a : menuList)
    {
        rndrTxtre.draw(*a);
    }
    rndrTxtre.display();
    spr.setTexture(rndrTxtre.getTexture(),true);
}
void Menu::step(float dt)
{
   int deltaScroll = 0;
   sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(Application::getWindow()));
   if(scroll && contains(scrollBar.getPosition().x,spr.getPosition().y,scrollBar.getSize().x,view.getSize().y,mouse.x,mouse.y))
    {
        float relMouseY = mouse.y - spr.getPosition().y;
        int new_scrolled = (menuList.size()-itemsVisible+1)*relMouseY/(view.getSize().y);
        if(new_scrolled != scrolled)
        {
            update = true;
            deltaScroll = new_scrolled-scrolled;
        }
    }
}
void Menu::passEvent(const sf::Event &event)
{
    bool update = false;
    int deltaScroll = 0;
    if(event.type == sf::Event::KeyPressed)
    {
        switch(event.key.code)
        {
            case sf::Keyboard::Up:
                if(--marker < 0)
                {
                    marker = menuList.size()-1;
                    deltaScroll = menuList.size()-itemsVisible;
                }
                else if(marker < scrolled)
                    deltaScroll = -1;
                update = true;
                break;
            case sf::Keyboard::Down:
                if(size_t(++marker) > menuList.size()-1)
                {
                    deltaScroll = -menuList.size()+itemsVisible;
                    marker = 0;
                }
                else if(marker-scrolled+1>itemsVisible)
                    deltaScroll = 1;
                update = true;
                break;
            case sf::Keyboard::Return:
                selected = true;
                break;
            default:
                break;
        }
    }
    else if(event.type == sf::Event::MouseMoved)
    {
        sf::Vector2f mouse(event.mouseMove.x,event.mouseMove.y);
        if(spr.getGlobalBounds().contains(mouse))
        {
            mouse -= spr.getPosition();
            mouse = rndrTxtre.mapPixelToCoords(static_cast<sf::Vector2i>(mouse));
            if(mouse.y/(linePadding+characterSize) != marker && mouse.y/(linePadding+characterSize)-scrolled <= itemsVisible)
            {
                marker = mouse.y/(linePadding+characterSize);
                update = true;
            }
        }
    }
    else if(event.type == sf::Event::MouseWheelMoved)
    {
        if(-event.mouseWheel.delta+scrolled+itemsVisible <= int(menuList.size()) && -event.mouseWheel.delta+scrolled >= 0)
        {
            sf::Vector2f mouse(event.mouseWheel.x,event.mouseWheel.y);
            if(spr.getGlobalBounds().contains(mouse))
            {
                deltaScroll = -event.mouseWheel.delta;
                update = true;
                mouse.y += deltaScroll*(linePadding+characterSize);//adjust for the new scroll
                mouse -= spr.getPosition();
                mouse = rndrTxtre.mapPixelToCoords(static_cast<sf::Vector2i>(mouse));
                if(mouse.y/(linePadding+characterSize) != marker && mouse.y/(linePadding+characterSize)-scrolled <= itemsVisible)
                    marker = mouse.y/(linePadding+characterSize);
            }
        }
    }
    else if(event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2f mouse(event.mouseButton.x,event.mouseButton.y);
        if(spr.getGlobalBounds().contains(mouse))
        {
            sf::Vector2f mouse2 = mouse - spr.getPosition();
            mouse2 = rndrTxtre.mapPixelToCoords(static_cast<sf::Vector2i>(mouse2));
            if(mouse2.y/(linePadding+characterSize) != marker && mouse2.y/(linePadding+characterSize)-scrolled <= itemsVisible)
            {
                marker = mouse2.y/(linePadding+characterSize);
                update = true;
            }
        }
    }

    if(update)  updateTexture(deltaScroll);
}
void Menu::updateTexture(int deltaScroll)
{
    selectionBg.setPosition(0,marker*(linePadding+characterSize));
    if(deltaScroll)
    {
        scrolled += deltaScroll;
        scrollBar.setPosition(scrollBar.getPosition().x,spr.getPosition().y+(view.getSize().y-scrollBar.getSize().y)*scrolled/(menuList.size()-itemsVisible));
        view.move(0,deltaScroll*(linePadding+characterSize));
    }
    rndrTxtre.setView(view);
    rndrTxtre.clear(sf::Color::White);
    rndrTxtre.draw(selectionBg);
    for(const auto &a : menuList)
    {
        rndrTxtre.draw(*a);
    }
    rndrTxtre.display();
}
