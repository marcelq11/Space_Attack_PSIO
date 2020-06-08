#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet: public sf::Sprite
{
public:
    Bullet(sf::Vector2f position);

    void setSpeed(int speed_y);
    void animate(const sf::Time &elapsed);

private:
    int speed_y_ = 0;
    int bullet_fr_ = 0;
};
#endif // BULLET_H
