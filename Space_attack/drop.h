#ifndef DROP_H
#define DROP_H

#include <SFML/Graphics.hpp>

class Drop: public sf::Sprite
{
public:
    Drop(sf::Vector2f position);
    //void setSpeed(int speed);
    void animate(const sf::Time &elapsed);
    void setdrop_number(int s);
    int getdrop_number();

private:
    int speed_y_ = 150;
    int drop_number_ = 0;
};

#endif // DROP_H
