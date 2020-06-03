#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy: public sf::Sprite
{
public:
    Enemy(sf::Vector2f position);
};

#endif // ENEMY_H
