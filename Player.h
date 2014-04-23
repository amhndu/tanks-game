#ifndef PLAYER_H
#define PLAYER_H
#include "Tank.h"

class Player
{
public:
    static const int maxlife = 100;
    Player() = default;
    Player(Tank *val,const std::string& name = "Player");
    void fire();
    inline const std::string& getName() { return playerName; }
    inline Tank &getTank() { return *myTank; }
    inline void setTank(Tank *t){myTank = t;}
    inline void rotateTurret(float f){ myTank->turret.rotate(f); }
    inline void setPower(float pow){ power=pow;}
    inline float getPower(){ return power; }
    inline void setTankPos(const sf::Vector2f& pos) { myTank->setPosition(pos); }
    inline float getTurretAngle(){ return myTank->turret.getRotation(); }
    inline const sf::Vector2f& getTankPos() { return myTank->tank.getPosition(); }
    inline void moveTank(int dir){ myTank->setMovement(dir); } //left: -1, right: 1
    inline void setLife(int l){life = l;}
    inline int getLife() { return life; }
    inline bool isDead(){return !(life);}
private:
    Tank *myTank;
    std::string playerName;
    int life;
    float power; //in range [0,1]
};
typedef std::unique_ptr<Player> Playerptr;
#endif // PLAYER_H
