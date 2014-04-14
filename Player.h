#ifndef PLAYER_H
#define PLAYER_H
#include "Tank.h"

class Player
{
public:
    static const int maxlife = 100;
    Player() = default;
    Player(Tank *val);
    Tank &getTank() { return *myTank; }
    void setTank(Tank *t){myTank = t;}
//    void setTurretAngle(float f){ myTank->turret.setRotation(f); }
    void rotateTurret(float f){ myTank->turret.rotate(f); }
    void setPower(float pow){ power=pow;}
    float getPower(){ return power; }
    float getTurretAngle(){ return myTank->turret.getRotation(); }
    const sf::Vector2f& getTankPos() { return myTank->tank.getPosition(); }
//    void setTankPos(const sf::Vector2f& pos) { myTank->tank.setPosition(pos); }
    void fire();
    void moveTank(int dir){ myTank->setMovement(dir); } //left: -1, right: 1
    void setLife(int l){life = l;}
    inline int getLife() { return life; }
    inline bool isDead(){return !(life);}
private:
    Tank *myTank;
    int life;
    float power; //in range [0,1]
    bool settingRot;
};
typedef std::unique_ptr<Player> Playerptr;
#endif // PLAYER_H
