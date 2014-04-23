#include "Player.h"
#include "Application.h"
#include "Missile.h"
#include "utilities.h"
#include "WorldText.h"

Player::Player(Tank *val,const std::string& name) :
    myTank(val),
    playerName(name),
    life(maxlife),
    power(0.4)
{}
void Player::fire()
{
    double phi = TO_RAD(myTank->turret.getRotation());
    double sin = std::sin(phi) , cos = std::cos(phi);
    double TankVelocity = power*500;
    Missile *m=new Missile(myTank->turret.getPosition().x + myTank->turret.getLocalBounds().width * cos,
                             myTank->turret.getPosition().y + myTank->turret.getLocalBounds().width * sin);
    m->setVelocity(TankVelocity * cos, TankVelocity * sin);
    Application::getGame().addWorldObj(m);
    Application::getMsgStream().sendMessage(Message("PlayerTurnOver"),"GameState");
}
