#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy: public sf::Sprite
{
public:
    Enemy(sf::Vector2f position,int hp);
    bool colision(sf::FloatRect &bullet);
    void animate(const sf::Time &elapsed);
    void setSpeed(int speed_x);
    bool bound_collision(float, float);
    int getHp();
    int getRight();
    int getLeft();
    int getBottom();
    int getSpeed();
private:
    int hp_ = 1;
    int left_bound_ = 0;
    int right_bound_ = 0;
    int bottom_bound_ = 0;
    int speed_x_ = 50;
};

#endif // ENEMY_H
