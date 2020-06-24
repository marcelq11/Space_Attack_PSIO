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

void Enemy::animate(const sf::Time &elapsed)
{
    move(speed_x_*elapsed.asSeconds(),0);
}

void Enemy::setSpeed(int speed_x)
{
  speed_x_=speed_x;
}

int Enemy::getHp()
{
    return hp_;
}

int Enemy::getSpeed()
{
    return speed_x_;
}

int Enemy::getLeft()
{
    sf::FloatRect enemy = getGlobalBounds();
    return enemy.left;
}

int Enemy::getRight()
{
    sf::FloatRect enemy = getGlobalBounds();
    return enemy.left + enemy.width;
}

int Enemy::getBottom()
{
    sf::FloatRect enemy = getGlobalBounds();
    return enemy.top + enemy.height;
}

bool Enemy::bound_collision(float left, float right)
{
    if(getLeft()<=left||getRight()>=right)
    {
        return true;
    }
    return false;

}
