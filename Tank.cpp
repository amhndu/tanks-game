#include "Tank.h"
#include "Application.h"
#include "Missile.h"
#include "utilities.h"
#include "WeaponPostEffects.h"

#define HMAP(n)        Application::getGame().getLandHeight(n)
#define R_POINTDIST(n) (cachedSqrt(1 + (HMAP(n) - HMAP((n)+1))*(HMAP(n) - HMAP((n)+1)))+0.5)
#define L_POINTDIST(n) (-cachedSqrt(1+ (HMAP((n)-1) - HMAP(n))*(HMAP((n)-1) - HMAP(n)))-0.5)
#define TANK_WIDTH     tank.getLocalBounds().width
#define TANK_HEIGHT    tank.getLocalBounds().height

const float lvelocity = 150;

Tank::Tank() :
    WorldObject(TankType) ,
    myOwner(nullptr) ,
    moving() ,
    tank(Application::getTexture(TankTexture)) ,
    turret(Application::getTexture(TurretTexture)),
    lifeBg(sf::Vector2f(TANK_WIDTH,5)),
    lifeFill(sf::Vector2f()),
    freefall(true),
    velocity(),
    Name(),
    fadingLife(true),
    fadingTimer(1)
{
    Application::getGame().incCounter();
    tank.setOrigin(tank.getLocalBounds().width / 2, tank.getLocalBounds().height);
    setPosition(sf::Vector2f());
    turret.setRotation(-45);
    lifeBg.setOutlineColor(sf::Color::Black);
    lifeBg.setOutlineThickness(1);
    lifeBg.setFillColor(sf::Color::Yellow);
    lifeFill.setFillColor(sf::Color::Red);
    Name.setColor(sf::Color::Black);
    Name.setCharacterSize(15);
    Name.setFont(Application::getFont(UbuntuCondensed));
}
Tank::~Tank()
{
    if(freefall)
        Application::getGame().decCounter();
}
sf::RectangleShape Tank::getTankRect()
{
    sf::RectangleShape rs(sf::Vector2f(tank.getLocalBounds().width,tank.getLocalBounds().height));
    rs.setPosition(tank.getPosition().x,tank.getPosition().y-TANK_HEIGHT/2);
    return rs;
}
void Tank::weapAct(float dlife)
{
    int newlife = std::max(0.0f,myOwner->getLife()-dlife);
    assert(newlife<=Player::maxlife);
    myOwner->setLife(newlife);
    if(newlife == 0)
    {
        selfDestruct = true;
        Application::getMsgStream().sendMessage(Message("TankDestroyed"),"GameState");
    }
    setLifeFill(newlife);
    fadingLife = true;
    fadingTimer = 1;
    lifeBg.setFillColor(lifeBg.getFillColor()+sf::Color(0,0,0,255));
    lifeBg.setOutlineColor(lifeBg.getOutlineColor()+sf::Color(0,0,0,255));
    lifeFill.setFillColor(lifeFill.getFillColor()+sf::Color(0,0,0,255));
    Name.setColor(Name.getColor()+sf::Color(0,0,0,255));
}
void Tank::setPlayer(Player *p)
{
    myOwner = p;
    Name.setString(p->getName());
    setLifeFill(p->getLife());
}
void Tank::setLifeFill(int l)
{
    lifeFill.setSize(sf::Vector2f(l*lifeBg.getSize().x/100,lifeBg.getSize().y));
}
void Tank::receiveMessage(const Message& msg)
{}
void Tank::handleCollision(WorldObject &b)
{
    switch(b.type)
    {
    case LandType:
        if(freefall)
        {
            int x0 = tank.getPosition().x , y0 = tank.getPosition().y;
            int h = constants::windowHeight-HMAP(x0);
            if(h <= y0)//collision
            {
                float ang = Application::getGame().getLandNormAng(x0,y0);
                tank.setRotation(std::fmod(90 - TO_DEG(ang),360) );
                freefall = false;
                velocity = sf::Vector2f();
                Application::getGame().decCounter();
                setPosition(x0,h);
                break;
            }
        }
        break;
    case WeaponType:
    case WeaponPostEffectType:
        b.handleCollision(*this);
        break;
    default:
        break;
    }
}

void Tank::draw(sf::RenderTarget &target)
{
    target.draw(turret);
    target.draw(tank);
    if(lifeFill.getFillColor().a != 0)
    {
        target.draw(lifeBg);
        target.draw(lifeFill);
        target.draw(Name);
    }
}
void Tank::setMovement(int val) {   moving = val;   }
void Tank::step(float dt)
{
    if(freefall)
    {
        velocity.y += constants::gravity*dt;
        sf::Vector2f ds = velocity*dt;
        tank.move(ds);
        turret.move(ds);
        lifeBg.move(ds);
        lifeFill.move(ds);
        Name.move(ds);
    }
    else
    {
        if(tank.getPosition().y<constants::windowHeight-HMAP(tank.getPosition().x))
        {
            freefall = true;
            Application::getGame().incCounter();
        }
        if(moving)
        {
            float phi = TO_RAD(tank.getRotation());
            //xvel is the horizontal component of the velocity with the angle phi.
            //we set the minimum velocity to 2 pixels/second
            //(moving<0)?-1:1 multiplies xvel by -1 if moving in the left direction
            float xvel = std::max(2.0f,lvelocity*std::cos(phi))*((moving<0)?-1:1);
            sf::Vector2f ds(xvel*dt,0);
            ds.y = constants::windowHeight-HMAP(tank.getPosition().x+ds.x)-tank.getPosition().y;
            moving = 0;
            if(ds.y < 0 && std::abs(ds.y/ds.x) > std::tan(TO_RAD(80))) //if ascend (going up) is too steep
                return;
            tank.move(ds);
            turret.move(ds);
            lifeBg.move(ds);
            lifeFill.move(ds);
            Name.move(ds);
            float ang = Application::getGame().getLandNormAng(tank.getPosition().x,tank.getPosition().y);
            tank.setRotation(std::fmod(90 - TO_DEG(ang),360) );
        }
    }
    sf::Vector2f dist = sf::Vector2f(sf::Mouse::getPosition(Application::getWindow())) - tank.getPosition();
    if(sq(dist.x)+sq(dist.y) <= sq(50))
    {
        fadingLife = true;
        fadingTimer = 1;
        lifeBg.setFillColor(lifeBg.getFillColor()+sf::Color(0,0,0,255));
        lifeBg.setOutlineColor(lifeBg.getOutlineColor()+sf::Color(0,0,0,255));
        lifeFill.setFillColor(lifeFill.getFillColor()+sf::Color(0,0,0,255));
        Name.setColor(Name.getColor()+sf::Color(0,0,0,255));
    }
    else if(fadingLife && (fadingTimer-=dt) < 0)
    {
        if(lifeBg.getFillColor().a != 0)
        {
            const float rate = 255.0/1;//fade out in 1 second
            int dAlpha = rate*dt;
            lifeFill.setFillColor(lifeFill.getFillColor()-sf::Color(0,0,0,dAlpha));
            lifeBg.setFillColor(lifeBg.getFillColor()-sf::Color(0,0,0,dAlpha));
            lifeBg.setOutlineColor(lifeBg.getOutlineColor()-sf::Color(0,0,0,dAlpha));
            Name.setColor(Name.getColor()-sf::Color(0,0,0,dAlpha));
        }
        else
            fadingLife = false;
    }
}
void Tank::reset()
{
    moving = 0;
    turret.setRotation(-45);
    if(!freefall)
    {
        freefall = true;
        Application::getGame().incCounter();
    }
}
void Tank::setPosition(const sf::Vector2f& pos)
{
    tank.setPosition(pos);
    turret.setPosition(pos-sf::Vector2f(0,TANK_HEIGHT/2));
    lifeBg.setPosition(pos.x-lifeBg.getGlobalBounds().width/2,pos.y-std::max(TANK_HEIGHT,TANK_WIDTH)-turret.getLocalBounds().width);
    lifeFill.setPosition(lifeBg.getPosition());
    Name.setPosition(pos.x-Name.getLocalBounds().width/2,lifeBg.getPosition().y-lifeBg.getLocalBounds().height-Name.getLocalBounds().height);
}
