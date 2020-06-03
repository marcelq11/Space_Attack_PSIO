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
#include "texturemanager.h"


int main()
{
    //TextureLoad
    TextureManager::loadTexture("Back1","Textures/back1.png");
    TextureManager::loadTexture("Player1","Textures/player.png");
    TextureManager::loadTexture("LaserG","Textures/laserGreen.png");
    TextureManager::loadTexture("Enemy","Textures/enemyUFO.png");

    //////
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    window.setFramerateLimit(60);

    /////Background
    sf::Sprite back;
    back.setTexture(*TextureManager::getTexture("Back1"));
    back.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

    sf::Clock clock;
    sf::Clock delay;

    //Objects
    ////Player
    Player player(sf::Vector2f(window.getSize().x/2,window.getSize().y-(window.getSize().y/12)));
    player.setTexture(*TextureManager::getTexture("Player1"));
    player.setScale(0.5,0.5);
    player.setBounds(0,window.getSize().x);
    player.setSpeed(200);

    ////Enemies
    Enemy enemy1(sf::Vector2f(400,30));
    enemy1.setTexture(*TextureManager::getTexture("Enemy"));
    enemy1.setScale(0.5,0.5);

    ////Bullet
    std::vector<Bullet> bulletVec;


    while (window.isOpen()) {
        // EVENTS
        sf::Event event;
        sf::Time elapsed = clock.restart();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // LOGIC

        player.animate(elapsed);

        if (delay.getElapsedTime().asMilliseconds()>200) {

                    Bullet bullet(sf::Vector2f((player.getLeft()+player.getRight())/2,(player.getTop()-15)));
                    bullet.setSpeed(-300);
                    bullet.setScale(0.5,0.5);
                    bullet.setTexture(*TextureManager::getTexture("LaserG"));
                    bulletVec.push_back(bullet);
                    delay.restart();
        }

    // DRAW
    window.draw(back);

    for(int i = 0; i < (int)bulletVec.size(); i++){
        bulletVec[i].animate(elapsed);
        window.draw(bulletVec[i]);
        if(bulletVec[i].getPosition().y < 0){
            bulletVec.erase(bulletVec.begin()+i);
        }
    }

    window.draw(player);
    window.draw(enemy1);

    window.display();
    }




    return 0;
}
