#include "bullet.h"

Bullet::Bullet( sf::Vector2f position)
{
setPosition(position);
}

void Bullet::setSpeed(int speed_y)
{
    speed_y_=speed_y;
}

void Bullet::animate(const sf::Time &elapsed)
{
    move(0,speed_y_*elapsed.asSeconds());
}
void Bullet::setDmg(int dmg)
{
    dmg_ = dmg;
}

int Bullet::getDmg()
{
    return dmg_;
}
