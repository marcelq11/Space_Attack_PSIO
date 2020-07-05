#include "player.h"


Player::Player(sf::Vector2f position, int hp)
{
setPosition(position);
hp_ = hp;
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
            !(rectangle_bounds.top <= top_bound_)) {
        move(0,-abs(speed_y_)*elapsed.asSeconds());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
            !(rectangle_bounds.top+rectangle_bounds.height >= bottom_bound_)) {
        move(0,abs(speed_y_)*elapsed.asSeconds());
    }
}

void Player::setBounds(int left, int right , int top ,int bottom)
{
    left_bound_ = left;
    right_bound_ = right;
    top_bound_ = top;
    bottom_bound_ = bottom;
}

bool Player::collision(sf::FloatRect position)
{
    if(getGlobalBounds().intersects(position))
    {
        return true;
    }
    return false;
}

void Player::setSpeed(int speed_x ,int speed_y)
{
    speed_x_=speed_x;
    speed_y_=speed_y;
}

void Player::setSpeed(float i)
{
    speed_x_*=i;
    speed_y_*=i;
}

void Player::setShoot_fr(float fr)
{
    shoot_fr_ = fr;
}
float Player::getShoot_fr()
{
    return shoot_fr_;
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

int Player::getHp()
{
    return hp_;
}

void Player::setHp(int i)
{
    hp_+=i;
}

int Player::getShoot_pattern()
{
    return shoot_pattern_;
}

void Player::iShoot_pattern(int i)
{
    shoot_pattern_+=i;
}

void Player::setPoint(int i)
{
    points_+=i;
}

int Player::getPoint()
{
    return points_;
}

int Player::getSpeed()
{
    return speed_x_;
}

