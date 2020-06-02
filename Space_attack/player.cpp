#include "player.h"



Player::Player(sf::Vector2f size,sf::Vector2f position): sf::RectangleShape(size)
{
setPosition(position);
}

void Player::animate(const sf::Time &elapsed)
{
    sf::FloatRect rectangle_bounds = getGlobalBounds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
            !(rectangle_bounds.left+rectangle_bounds.width >= right_bound_)) {
        move(abs(speed_x_)*elapsed.asSeconds(),0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
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

int Player::getLeft()
{
    sf::FloatRect player = getGlobalBounds();
    return player.left;
}

int Player::getRight()
{
    sf::FloatRect player = getGlobalBounds();
    return player.left + player.width;
}

int Player::getTop()
{
    sf::FloatRect player = getGlobalBounds();
    return player.top;
}

