#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>


class Player: public sf::RectangleShape
{
public:
    Player(sf::Vector2f size,sf::Vector2f position);
    void animate(const sf::Time &elapsed);
    void setBounds(int left, int right);
    void setSpeed(int speed_x_);
    int getRight();
    int getLeft();
    int getTop();



private:
    int left_bound_ = 0;
    int right_bound_ = 0;
    int speed_x_ = 0;
    sf::RectangleShape player;
};

#endif // PLAYER_H
