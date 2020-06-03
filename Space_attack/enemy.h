#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy: public sf::Sprite
{
public:
    Enemy(sf::Vector2f position,int hp);
    bool colision(sf::FloatRect &bullet);
    int getHp();
private:
    int hp_ = 1;
};

#endif // ENEMY_H
