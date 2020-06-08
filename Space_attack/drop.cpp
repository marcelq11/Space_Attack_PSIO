#include "drop.h"

Drop::Drop(sf::Vector2f position)
{
setPosition(position);
}
/*void Drop::setSpeed(int speed)
{
    speed_y_ = speed;
}*/
void Drop::animate(const sf::Time &elapsed)
{
    move(0,speed_y_*elapsed.asSeconds());
}
