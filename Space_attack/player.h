#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>


class Player: public sf::RectangleShape
{
public:
    Player(sf::Vector2f size,sf::Vector2f position);
    void animate(const sf::Time &elapsed);
    void setBounds(int left, int right);


private:
    int left_bound = 0;
    int right_bound = 0;
};

#endif // PLAYER_H
