#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "player.h"
#include "bullet.h"
#include "enemy.h"


int main()
{
        sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
        window.setFramerateLimit(5);
        Player player(sf::Vector2f (40.0, 20.0), sf::Vector2f(window.getSize().x/2,window.getSize().y-(window.getSize().y/20)));
        std::vector<Bullet> bulletVec;
        player.setBounds(0,window.getSize().x);
        player.setSpeed(200);

        sf::Clock clock;
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

            Bullet bullet(sf::Vector2f(2,30),sf::Vector2f((player.getLeft()+player.getRight())/2,player.getTop()));
            bullet.setSpeed(-300);
            bulletVec.push_back(bullet);

            // DRAW
            for(int i = 0; i < (int)bulletVec.size(); i++)
            {
                bulletVec[i].animate(elapsed);
                window.draw(bulletVec[i]);
            }
            window.draw(player);
            window.draw(bullet);


            window.display();
        }




    return 0;
}
