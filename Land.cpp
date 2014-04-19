/*
	No rights Reserved.
	Amish Kumar Naidu
	amhndu at gmail.com
*/
#include "Land.h"
#include "Application.h"
#include "utilities.h"
#include "simplexnoise.h"

Land::Land() :
    WorldObject(LandType),
    LandModified(false),
    hmap(constants::windowWidth),
    slColumns(),
    LandSpr(),
    LandImg(),
    LandTexture()
{
    LandImg.create(constants::windowWidth, constants::windowHeight, sf::Color::Transparent);
}
void Land::destroyCircle(int x0, int y0, int radius)
{
    int x = 0 , y = radius;
    int sqradius = radius*radius;
    while( x < radius )
    {
        destroyColumn(x0+x,y0-y,y0+y);
        destroyColumn(x0-x,y0-y,y0+y);
        ++x;
        y = cachedSqrt(sqradius-x*x)+0.5;
    }
}
void Land::destroyColumn(int x,int top,int bottom)
{
    if(!isInWindow(x,0))
        return;
    int LandTop = constants::windowHeight-hmap[x];
    bottom = std::min(bottom,constants::windowHeight-1);
    top = std::max(0,top);
    if(bottom > LandTop)
    {
    // We have two cases ,
        // case 1 the part is inside the Land , making a cavity
        if(top > LandTop)
        {
            for(int iy = top; iy <= bottom ; ++iy)
                LandImg.setPixel(x,iy,sf::Color::Transparent);
            std::list<slManifest> &slColList = slColumns[x];
            slManifest cav{top,bottom,60};
            for(auto i = slColList.begin() ;;) //insert the cavity appropriately into the list
            {
                if(cav.dest < i->src || i == slColList.end())
                {
                    slColList.insert(i,cav);
                    break;
                }
                if(i->intersects(cav)) //then merge i to cav and continue with the new i
                {
                    cav.merge(*i);
                    i = slColList.erase(i);
                }
                else ++i;
            }
            Application::getMsgStream().sendMessage(Message("SetLandSlide"),"GameState");
        }
        // case 2 the part is on the surface , it makes a crater
        else
        {
            for(int iy = LandTop; iy <= bottom ; ++iy)
                LandImg.setPixel(x,iy,sf::Color::Transparent);
            hmap[x] = constants::windowHeight-bottom;
        }
        hmap[x] = std::max(hmap[x],0);
        LandModified = true;
    }
}
void Land::step(float dt)
{
//    if(LandModified) //last iteration's flag
//    {
//        LandTexture.loadFromImage(LandImg);
//        Application::getMsgStream().getGroup("Tanks").sendMessage(Message("LandModified"));
//        LandModified = false;
//    }
    std::list<int> colrem;//columns to remove
    for(auto &i : slColumns)
    {
        std::list<slManifest> &slColList = i.second;
        int x = i.first;
        for(auto j = slColList.rbegin(); j != slColList.rend() ; ++j)
        {
            bool doneSliding = false; //whether the cavity has been filled due to sliding
            j->velocity += constants::gravity*dt;
            int ds = j->velocity*dt+0.5 , ulim = constants::windowHeight-hmap[x];
            if(ds <= 0) continue;
            if(ds + j->src >= j->dest)
            {
                ds = j->dest - j->src + 1;
                j->src = j->dest;
                doneSliding = true;
            }
            else    j->src += ds;
            auto upperCol = std::next(j);
            if(upperCol != slColList.rend())
                ulim = (upperCol->dest += ds);
            else
                hmap[x] = std::max(0,hmap[x]-ds);
            for(int k = j->src;k >= ulim;--k)
            {
               //for (x,k) set the pixel to (x,k-ds) i.e. move the pixels below by ds
               LandImg.setPixel(x , k ,
                                (k-ds>=0)?LandImg.getPixel(x,k-ds):sf::Color::Transparent);
            }
            if(doneSliding)
            {
                auto jminus1 = std::prev(j);
                slColList.erase(std::prev(j.base()));
                j = jminus1;
            }
        }
        if(slColList.empty()) //if no cavities
        {
            colrem.push_back(x);
        }
        LandModified = true;
    }
    for(int x : colrem)
    {
        slColumns.erase(x);
        if(slColumns.empty())
        {
            Application::getMsgStream().sendMessage(Message("UnsetLandSlide"),"GameState");
        }
    }
}
void Land::draw(sf::RenderTarget &target)
{
    if(LandModified)
    {
        LandTexture.loadFromImage(LandImg);
        LandModified = false;
    }
    target.draw(LandSpr);
}
void Land::reset()
{
    hmap.resize(constants::windowWidth);
}
int Land::getHeight(int x)
{
    if(x >= 0 && x < int(hmap.size()))
    {
        return hmap[x];
    }
    return 0;
}
sf::Vector2f Land::getNormal(int x,int y)
{
    //Calculate the weighted average of the solid pixels to get the normal
    float avgX = 0;
    float avgY = 0;
    int sq = 4;//size of the square to calculate the average
    for(int w = -sq; w <= sq; w++)
    {
      for(int h = -sq; h <= sq; h++)
      {
        if(isPixelSolid(x+w,y+h))
        {
          avgX -= w;
          avgY -= h;
        }
      }
    }
    float mod = std::hypot(avgX,avgY);
    return (mod)?sf::Vector2f(avgX/mod,avgY/mod):sf::Vector2f();
}
float Land::getNormAngle(int x,int y)
{
    //Calculate the weighted average of the solid pixels to get the normal
    float avgX = 0,avgY = 0;
    int sq = 4;//size of the square to calculate the average
    for(int w = -sq; w <= sq; w++)
    {
      for(int h = -sq; h <= sq; h++)
      {
        if(isPixelSolid(x + w, y + h))
        {
          avgX -= w;
          avgY -= h;
        }
      }
    }
    return arctan(-avgY,avgX);
}
void Land::genHeightMap(Landtype Land_t)
{
    if(Land_t == Random) { Land_t = Landtype(rand() % Random); }
    int octaves, llim = 0, ulim = constants::windowHeight;
    double persistance, scale, detail;
    switch(Land_t)
    {
    case Flats: //Many magic numbers here , found by trial and error
        octaves = 1;
        persistance = 1;
        scale = 1;
        detail = constants::windowWidth * 1.25;
        ulim = constants::windowHeight * 2 / 3.0 - 100;
        llim = constants::windowHeight / 3.0;
        break;
    case Hilly:
        octaves = 4;
        persistance = 0.4;
        scale = 1;
        detail = constants::windowWidth / 3.0;
        break;
    case Valley:
        octaves = 4;
        persistance = 0.2;
        scale = 1;
        detail = constants::windowWidth / 2.0;
        break;
    default:
        octaves = 8;
        persistance = 0.75;
        scale = 1;
        detail = constants::windowWidth / 3.0;
        break;
    }
    LandImg.create(LandImg.getSize().x,LandImg.getSize().y,sf::Color::Transparent);
    double offsetx = (rand() % 1000);
    double y = rand() % 1000;
    for(int i = 0; i < constants::windowWidth; i++)
    {
        hmap[i] = scaled_octave_noise_2d(octaves, persistance, scale, llim, ulim, double(i + offsetx) / detail, y / detail);
        for(int h = constants::windowHeight - hmap[i]; h < constants::windowHeight ; ++h)
        {
            LandImg.setPixel(i, h, grad(double(constants::windowHeight - h) / (hmap[i]),
                                        sf::Color(150, 155, 0), sf::Color(50, 150, 50)));
        }
    }
    LandTexture.loadFromImage(LandImg);
    LandSpr.setTexture(LandTexture);
}
void Land::handleCollision(WorldObject &b)
{
    switch(b.type)
    {
    case TankType:
        b.handleCollision(*this);
    case WeaponType:
        b.handleCollision(*this);
        break;
    default:
        break;
    }
}
void Land::receiveMessage(const Message& msg)
{
    if(msg.ID == "DestroyCircle")
    {
        sf::Vector2i pos = msg.getItem<sf::Vector2i>(0);
        int r = msg.getItem<int>(1);
        destroyCircle(pos.x,pos.y,r);
    }
}
bool Land::isPixelSolid(int x,int y)
{
    if(isInRange(size_t(x),size_t(0),hmap.size()))
        return LandImg.getPixel(x,y) != sf::Color::Transparent;
    return true;//outside the window consider the pixels  to be solid
}
