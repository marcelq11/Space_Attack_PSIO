#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bullet.h"
#include "drop.h"
#include "enemy.h"
#include "other.h"
#include "player.h"
#include "texturemanager.h"


int main()
{
    //TextureLoad
    TextureManager::loadTexture("Back1","Textures/back1.png");
    TextureManager::loadTexture("Player1","Textures/player.png");
    TextureManager::loadTexture("LaserG","Textures/laserGreen.png");
    TextureManager::loadTexture("LaserR","Textures/laserRed.png");
    TextureManager::loadTexture("Enemy","Textures/enemyShip.png");
    TextureManager::loadTexture("Drop","Textures/powerupRed_bolt.png");

    //////
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    window.setFramerateLimit(60);
    srand(time(NULL));

    /////Background
    sf::Sprite back;
    back.setTexture(*TextureManager::getTexture("Back1"));
    back.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));

    sf::Clock clock;
    sf::Clock delay;
    sf::Clock delayEnemy;

    //Objects
    ////Player
    Player player(sf::Vector2f(window.getSize().x/2,window.getSize().y-(window.getSize().y/12)),1);
    player.setTexture(*TextureManager::getTexture("Player1"));
    player.setScale(0.5,0.5);
    player.setBounds(0,window.getSize().x,0,window.getSize().y);
    player.setSpeed(200,200);
    player.setShoot_fr(300);

    ////Enemies

    std::vector<Enemy> enemyVec;
    for (int i = 0; i<7; i++)
    {
            for(int k=0; k<4; k++)
            {
            Enemy enemy(sf::Vector2f(((window.getSize().x-7*70)/2)+(i*70),30+k*70),1);
            enemy.setTexture(*TextureManager::getTexture("Enemy"));
            enemy.setScale(0.5,0.5);
            enemyVec.emplace_back(enemy);
            }
    }

    ////Bullet
    std::vector<Bullet> bulletVec;
    std::vector<Bullet> bulletEnemyVec;



    ////Drops
    std::vector<Drop> dropVec;
    Drop drop(sf::Vector2f(400,300));
    drop.setTexture(*TextureManager::getTexture("Drop"));
    drop.setScale(0.7,0.7);

    while (window.isOpen()) {
        // EVENTS
        sf::Event event;
        sf::Time elapsed = clock.restart();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // LOGIC
        ////Player
        player.animate(elapsed);

        ////Spawn enemy
        /*if(rand()%120 < 1 && enemyVec.size() < 12)
        {
            Enemy enemy (sf::Vector2f(rand()%(int)window.getSize().x,30),4);
            enemy.setTexture(*TextureManager::getTexture("Enemy"));
            enemy.setScale(0.5,0.5);
            enemyVec.emplace_back(enemy);
        }*/


        ////Bullet fill vector, add texture, set parameters player bullet
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
            if (delay.getElapsedTime().asMilliseconds()>player.getShoot_fr()) {
                Bullet bullet(sf::Vector2f((player.getLeft()+player.getRight())/2,(player.getTop()-15)));
                bullet.setSpeed(-300);
                bullet.setScale(0.5,0.5);
                bullet.setTexture(*TextureManager::getTexture("LaserG"));
                bulletVec.push_back(bullet);
                delay.restart();

            }
        }

        ////Enemy check collision with bullet, erase bullet, drowing enemy bullet
        for(int i = 0; i < (int)bulletVec.size(); i++){
            for(int k = 0; k < (int)enemyVec.size(); k++){
                    sf::FloatRect bullet = bulletVec[i].getGlobalBounds();
                    if(!enemyVec.empty()){
                        if(enemyVec[k].colision(bullet))
                        {
                            bulletVec.erase(bulletVec.begin()+i);
                        }
                    }
            }
        }
            for(auto &s : enemyVec)
            {
                if (delayEnemy.getElapsedTime().asSeconds()>(rand()%5)+2) {
                    Bullet bullet(sf::Vector2f((s.getLeft()+s.getRight())/2,(s.getBottom()+15)));
                    bullet.setSpeed(150);
                    bullet.setScale(0.5,0.5);
                    bullet.setTexture(*TextureManager::getTexture("LaserR"));
                    bulletEnemyVec.push_back(bullet);
                    delayEnemy.restart();
                }
            }



        ////Drop
        for(int i = 0; i < (int)enemyVec.size(); i++){
                if(!enemyVec[i].getHp()){
                    if(rand()%100 < 10)
                    {
                        Drop drop(sf::Vector2f(enemyVec[i].getPosition()));
                        drop.setTexture(*TextureManager::getTexture("Drop"));
                        drop.setScale(0.7,0.7);
                        dropVec.push_back(drop);
                    }
                    enemyVec.erase(enemyVec.begin()+i);
                }
            }

        for(int i = 0; i < (int)dropVec.size(); i++){
            dropVec[i].animate(elapsed);
            if(dropVec[i].getPosition().y > window.getSize().y){
                dropVec.erase(dropVec.begin()+i);
            }
        }

        /////Drop&Player
        for(int i = 0; i < (int)dropVec.size(); i++)
        {
            if(player.collision(dropVec[i].getGlobalBounds()))
            {
                player.setShoot_fr(player.getShoot_fr()*0.6);
                dropVec.erase(dropVec.begin()+i);
            }
        }

        // DRAW
        window.draw(back);

        ////Bullet
        for(int i = 0; i < (int)bulletVec.size(); i++){
            bulletVec[i].animate(elapsed);
            window.draw(bulletVec[i]);
            if(bulletVec[i].getPosition().y < 0){
                bulletVec.erase(bulletVec.begin()+i);
            }
        }

        ////BulletEnemy
        for(int i = 0; i < (int)bulletEnemyVec.size(); i++){
            bulletEnemyVec[i].animate(elapsed);
            window.draw(bulletEnemyVec[i]);
            if(bulletEnemyVec[i].getPosition().y < 0){
                bulletEnemyVec.erase(bulletEnemyVec.begin()+i);
            }
        }

        ////Enemy
        for(auto &s : enemyVec){
            s.animate(elapsed);
            if(s.bound_collision(0,window.getSize().x))
            {
                for(auto &s : enemyVec){
                    s.setSpeed(s.getSpeed()*(-1));
                }
            }
            window.draw(s);
        }

        ////Drop
        if(!dropVec.empty()){
            for(auto &s : dropVec){
                window.draw(s);
            }
        }
        ////Other
        window.draw(player);
        window.display();
    }

    return 0;
}
