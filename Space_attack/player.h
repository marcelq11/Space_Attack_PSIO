#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>


class Player: public sf::Sprite
{
public:
    Player(sf::Vector2f position, int hp);
    void animate(const sf::Time &elapsed);
    bool collision(sf::FloatRect);
    void setBounds(int left, int right, int top , int bottom);
    void setSpeed(int speed_x ,int speed_y);
    void setSpeed(float i);
    void setShoot_fr(float fr);
    void setHp(int i);
    void setPoint(int i);
    void iShoot_pattern(int i);
    int getRight();
    int getLeft();
    int getTop();
    int getShoot_pattern();
    int getHp();
    int getPoint();
    float getShoot_fr();
    int getSpeed();



private:
    int left_bound_ = 0;
    int right_bound_ = 0;
    int top_bound_ = 0;
    int bottom_bound_ = 0;
    int speed_x_ = 0;
    int speed_y_ = 0;
    float shoot_fr_ = 0;
    int shoot_pattern_ = 0;
    int hp_ = 1;
    int points_ = 0;
};

#endif // PLAYER_H
