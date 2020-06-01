#include "player.h"



Player::Player(sf::Vector2f size,sf::Vector2f position): sf::RectangleShape(size)
{
setPosition(position);
}

void Player::animate(const sf::Time &elapsed)
{
    sf::FloatRect rectangle_bounds = getGlobalBounds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
            !(rectangle_bounds.left+rectangle_bounds.width >= right_bound_)) {
        move(abs(speed_x_)*elapsed.asSeconds(),0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
            !(rectangle_bounds.left <= left_bound_)) {
        move(-abs(speed_x_)*elapsed.asSeconds(),0);
    }
}

void Player::setBounds(int left, int right)
{
    left_bound_=left;
    right_bound_=right;
}

void Player::setSpeed(int speed_x)
{
    speed_x_=speed_x;
}

