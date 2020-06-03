#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "other.h"


int main()
{
//    sf::Texture background1 = Load_texture("../Textures/back1.png");

//    sf::Sprite sprite1;
//    sprite1.setTexture(background1);
//    sprite1.setPosition(20,200);

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    window.setFramerateLimit(60);
    Player player(sf::Vector2f (40.0, 20.0), sf::Vector2f(window.getSize().x/2,window.getSize().y-(window.getSize().y/20)));
    std::vector<Bullet> bulletVec;
    player.setBounds(0,window.getSize().x);
    player.setSpeed(200);

    sf::Clock clock;
    sf::Clock delay;

    while (window.isOpen()) {
        // EVENTS
        sf::Event event;
        sf::Time elapsed = clock.restart();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // LOGIC
        window.clear(sf::Color::Black);

        player.animate(elapsed);

        if (delay.getElapsedTime().asMilliseconds()>300) {

                    Bullet bullet(sf::Vector2f(2,30),sf::Vector2f((player.getLeft()+player.getRight())/2,(player.getTop()-15)));
                    bullet.setSpeed(-300);
                    bulletVec.push_back(bullet);
                    delay.restart();
                }

        for(int i = 0; i < (int)bulletVec.size(); i++)
        {

            bulletVec[i].animate(elapsed);
            window.draw(bulletVec[i]);
            if(bulletVec[i].getPosition().y < 0)
            {
                bulletVec.erase(bulletVec.begin()+i);
            }
        }


        // DRAW
        window.draw(player);

        window.display();
    }




    return 0;
}
