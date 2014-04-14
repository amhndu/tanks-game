#include "WeaponPostEffects.h"
#include "Tank.h"
#include "utilities.h"
#include "Application.h"

Explosion::Explosion(AnimationType animType,sf::Vector2f pos,int r) :
    WorldObject(WeaponPostEffectType),
    expCircle(r),
    expAnim(AnimationCreator::create(animType,pos))
{
    expCircle.setOrigin(r,r);
    expCircle.setPosition(pos);
    Application::getMsgStream().sendMessage(Message("WeapObjCreated"),"GameState");
}
Explosion::~Explosion()
{
    Application::getMsgStream().sendMessage(Message("WeapObjDestroyed"),"GameState");
}
void Explosion::handleCollision(WorldObject &b)
{
    switch(b.type)
    {
    case WorldObject::TankType:
    {
        Tank &t = static_cast<Tank&>(b);
        bool &tankActed = tanksActedOn[&t];
        if(tankActed == false && intersects(expCircle,t.getTankRect()))
        {
            sf::Vector2f vec = expCircle.getPosition() - t.getTankRect().getPosition();
            float blowPower = 50*(1-std::hypot(vec.x,vec.y)/(expCircle.getRadius()+t.getTankRect().getLocalBounds().width/2));
            if(blowPower < 0)
            {
                PRINT_VAR(vec.x)
                PRINT_VAR(vec.y)
                PRINT_VAR(std::hypot(vec.x,vec.y))
            }
            t.weapAct(blowPower);
            tankActed = true;
        }
    }
        break;
    default:
        break;
    }
}
void Explosion::draw(sf::RenderTarget &target)
{
    if(expAnim->selfDestruct == true)
    {
        selfDestruct = true;
    }
    expAnim->draw(target);
}
void Explosion::step(float dt)
{
    expAnim->step(dt);
}
void Explosion::reset()
{
    selfDestruct = true;
}
