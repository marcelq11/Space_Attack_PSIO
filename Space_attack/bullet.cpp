#include "bullet.h"

Bullet::Bullet(sf::Vector2f size, sf::Vector2f position): sf::RectangleShape(size)
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
