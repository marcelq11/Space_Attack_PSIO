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
void Drop::setdrop_number(int s)
{
    drop_number_ = s;
}

int Drop::getdrop_number()
{
    return drop_number_;
}
