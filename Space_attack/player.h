#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>


class Player: public sf::Sprite
{
public:
    Player(sf::Vector2f position, int hp);
    void animate(const sf::Time &elapsed);
    void setBounds(int left, int right, int top , int bottom);
    void setSpeed(int speed_x ,int speed_y);
    void setShoot_fr(float fr);
    float getShoot_fr();
    bool collision(sf::FloatRect);
    int getRight();
    int getLeft();
    int getTop();
    void iShoot_pattern(int i);
    int getShoot_pattern();
    int getHp();
    void setHp(int i);
    void setPoint(int i);
    int getPoint();



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
