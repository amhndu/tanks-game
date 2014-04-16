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

const double lvelocity = 150;

Tank::Tank() :
    WorldObject(TankType) ,
    myOwner(nullptr) ,
    moving() ,
    moveRem() ,
    tank(Application::getTexture(TankTexture)) ,
    turret(Application::getTexture(TurretTexture)),
    lifeBg(sf::Vector2f(TANK_WIDTH,5)),
    lifeFill(sf::Vector2f()),
    freefall(true)
{
    Application::getGame().incCounter();
//    Application::getMsgStream().sendMessage(Message("TankFreeFall"),"GameState");
    tank.setOrigin(tank.getLocalBounds().width / 2, tank.getLocalBounds().height);
    setPosition(sf::Vector2f());
    turret.setRotation(-45);
    lifeBg.setOutlineColor(sf::Color::Black);
    lifeBg.setOutlineThickness(1);
    lifeBg.setFillColor(sf::Color::Yellow);
    lifeFill.setFillColor(sf::Color::Red);
}
Tank::~Tank()
{
    if(freefall)
    Application::getGame().decCounter();
//        Application::getMsgStream().sendMessage(Message("TankOnLand"),"GameState");
}
sf::RectangleShape Tank::getTankRect()
{
    sf::RectangleShape rs(sf::Vector2f(tank.getLocalBounds().width,tank.getLocalBounds().height));
    rs.setPosition(tank.getPosition().x,tank.getPosition().y-TANK_HEIGHT/2);
    return rs;
}
void Tank::weapAct(float dlife)
{
    PRINT_VAR(dlife)
    int newlife = std::max(0.0f,myOwner->getLife()-dlife);
    if(newlife == 0)
    {
        selfDestruct = true;
        Application::getGame().addWorldObj(new Explosion(MissileExplosionB,tank.getPosition(),20));
    }
    myOwner->setLife(newlife);
    setLifeFill(newlife);
    Application::getMsgStream().sendMessage(Message("TankDestroyed"),"GameState");
}
void Tank::setPlayer(Player *p)
{
    myOwner = p;
    setLifeFill(p->getLife());
}
void Tank::setLifeFill(int l)
{
    assert(l<=Player::maxlife);
    lifeFill.setSize(sf::Vector2f(l*lifeBg.getSize().x/100,lifeBg.getSize().y));
}
void Tank::receiveMessage(const Message& msg)
{
//    if(msg.ID == "LandModified" && freefall == false)
//    {
//        freefall = true;
//        Application::getMsgStream().sendMessage(Message("TankFreeFall"),"GameState");
//    }
}
void Tank::moveTank(double moveAmount) //A very crude algorithm implemented in a cruder way.
{
    int x0 = tank.getPosition().x;
    if((moveAmount+moveRem)*moveRem > 0) // when both have the same direction.
        moveAmount += moveRem;
    moveRem = 0;
    if((moveAmount < 0 && moveAmount > L_POINTDIST(x0)/2) ||
            (moveAmount > 0 && moveAmount < R_POINTDIST(x0)/2))
    {
        moveRem = moveAmount;
        return;
    }
    else { moveRem = 0; }
    if((x0 + TANK_WIDTH / 2 < constants::windowWidth || moveAmount < 0)
       && (x0 - TANK_WIDTH / 2 >= 0 || moveAmount > 0))
    {
        int xpos = x0;
        for(float sum = 0;;)
        {
            if(fabs(moveAmount) > fabs(sum) && xpos < constants::windowWidth && xpos >= 0)
            {
                sum += (moveAmount > 0) ? (xpos++, R_POINTDIST(xpos - 1)) : (xpos--, L_POINTDIST(xpos + 1));
            }
            else
            {
                moveRem = moveAmount - sum;
                break;
            }
        }
        setPosition(xpos,constants::windowHeight-HMAP(xpos));
        float ang = Application::getGame().getLandNormAng(xpos,constants::windowHeight-HMAP(xpos));
        tank.setRotation(std::fmod(90 - TO_DEG(ang),360) );
    }
}
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
//                Application::getMsgStream().sendMessage(Message("TankOnLand"),"GameState");
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
    target.draw(lifeBg);
    target.draw(lifeFill);
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
    }
    else
    {
        if(tank.getPosition().y<constants::windowHeight-Application::getGame().getLandHeight(tank.getPosition().x))
        {
            freefall = true;
            Application::getGame().incCounter();
//            Application::getMsgStream().sendMessage(Message("TankFreeFall"),"GameState");
        }
        if(moving < 0)
            moveTank((moving = 0, lvelocity * dt * -1));
        else if(moving > 0)
            moveTank((moving = 0, lvelocity * dt));
    }
}
void Tank::reset()
{
    moving = 0;
    moveRem = 0;
    turret.setRotation(-45);
    if(!freefall)
    {
        freefall = true;
        Application::getGame().incCounter();
//        Application::getMsgStream().sendMessage(Message("TankFreeFall"),"GameState");
    }
}
void Tank::setPosition(const sf::Vector2f& pos)
{
    tank.setPosition(pos);
    turret.setPosition(pos-sf::Vector2f(0,TANK_HEIGHT/2));
    lifeBg.setPosition(pos.x-lifeBg.getGlobalBounds().width/2,pos.y+TANK_HEIGHT+5);
    lifeFill.setPosition(lifeBg.getPosition());
}
