#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "player.h"

int main()
{
        sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
        window.setFramerateLimit(60);
        Player player1(sf::Vector2f (40.0, 20.0), sf::Vector2f(window.getSize().x/2,window.getSize().y-(window.getSize().y/20)));
        sf::Clock clock;
        player1.setBounds(0,window.getSize().x);


        while (window.isOpen()) {
            // EVENTS
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            // LOGIC
            window.clear(sf::Color::Black);

            sf::Time elapsed = clock.restart();
            player1.animate(elapsed);


            // DRAW
            window.clear(sf::Color::Black);
            window.draw(player1);


            window.display();
        }




    return 0;
}
