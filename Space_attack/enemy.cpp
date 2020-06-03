#include "enemy.h"

#include <iostream>

Enemy::Enemy(sf::Vector2f position,int hp)
{
setPosition(position);
hp_=hp;
}
bool Enemy::colision(sf::FloatRect &bullet)
{
    if(getGlobalBounds().intersects(bullet))
    {
        hp_--;
        return true;
    }
    return false;

}
int Enemy::getHp()
{
    return hp_;
}
