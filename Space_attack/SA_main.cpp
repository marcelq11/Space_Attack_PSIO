#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <QFile>
#include <QTextStream>

#include "bullet.h"
#include "drop.h"
#include "enemy.h"
#include "other.h"
#include "player.h"
#include "texturemanager.h"


int main()
{
    int cycle = 0;
    bool play = false;
    float fr = 40;
    QString line;
    //TextureLoad
    TextureManager::loadTexture("Back1","Textures/back1.png");
    TextureManager::loadTexture("Player1","Textures/player.png");
    TextureManager::loadTexture("LaserG1","Textures/laserGreen01.png");
    TextureManager::loadTexture("LaserG2","Textures/laserGreen02.png");
    TextureManager::loadTexture("LaserR","Textures/laserRed.png");
    TextureManager::loadTexture("Enemy","Textures/enemyShip.png");
    TextureManager::loadTexture("Drop1","Textures/drop1.png");
    TextureManager::loadTexture("Drop2","Textures/drop2.png");
    TextureManager::loadTexture("Drop3","Textures/drop3.png");
    TextureManager::loadTexture("Drop4","Textures/drop4.png");
    TextureManager::loadTexture("Drop5","Textures/drop5.png");
    TextureManager::loadTexture("Frame","Textures/buttonRed.png");
    TextureManager::loadTexture("Life","Textures/playerLife2_red.png");
    TextureManager::loadTexture("Play","Textures/Play.png");
    TextureManager::loadTexture("Quit","Textures/Quit.png");
    TextureManager::loadTexture("Game_over","Textures/game_over.png");

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
    Player player(sf::Vector2f(window.getSize().x/2,window.getSize().y-(window.getSize().y/12)),5);
    player.setTexture(*TextureManager::getTexture("Player1"));
    player.setScale(0.5,0.5);
    player.setBounds(0,window.getSize().x,0,window.getSize().y);
    player.setSpeed(200,200);
    player.setShoot_fr(300);

    ////Enemies
    std::vector<Enemy> enemyVec;

    ////Bullet
    std::vector<Bullet> bulletVec;
    std::vector<Bullet> bulletEnemyVec;

    ////Drops
    std::vector<Drop> dropVec;

    ////Score
    sf::Font myFont;

    if(!myFont.loadFromFile("Fonts/arial.ttf"))
    {
        std::cout<<"ERROR"<<std::endl;
    }
    sf::Text scoreText;
    scoreText.setFont(myFont);
    scoreText.setPosition(window.getSize().x - 120,0);
    scoreText.setScale(0.5,0.5);

    ////High score
    sf::Text highScore;
    highScore.setFont(myFont);
    highScore.setPosition(window.getSize().x/2-100,window.getSize().y/2+100);
    highScore.setFillColor(sf::Color::Red);

    ////HealthBar
    std::vector<sf::Sprite> lifeVec;
    sf::Sprite lifex;
    sf::Text liveText;
    liveText.setFont(myFont);
    liveText.setPosition(35,5);
    liveText.setScale(0.5,0.5);

    ////Menu
    sf::Sprite playbutton;
    playbutton.setPosition(window.getSize().x/2-100,200);
    playbutton.setTexture(*TextureManager::getTexture("Play"));
    sf::Sprite quitbutton;
    quitbutton.setPosition(window.getSize().x/2-100,280);
    quitbutton.setTexture(*TextureManager::getTexture("Quit"));
    sf::Sprite gameover;
    gameover.setPosition(window.getSize().x/2-80,window.getSize().y/2-100);
    gameover.scale(0.3,0.3);
    gameover.setTexture(*TextureManager::getTexture("Game_over"));


    while (window.isOpen()) {
        // EVENTS
        sf::Event event;
        sf::Time elapsed = clock.restart();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(!play)
        {
            if (event.type == sf::Event::MouseButtonPressed) {
                    if(event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                        if(playbutton.getGlobalBounds().intersects(sf::FloatRect(mouse_pos.x,mouse_pos.y,1,1)))
                        {
                            play = true;
                        }
                        if(quitbutton.getGlobalBounds().intersects(sf::FloatRect(mouse_pos.x,mouse_pos.y,1,1)))
                        {
                             window.close();
                        }
                    }
            }
            window.draw(back);
            window.draw(playbutton);
            window.draw(quitbutton);
            window.display();
        }
        else if(play && player.getHp()>0)
        {
            // LOGIC
            ////Player
            player.animate(elapsed);

            ////Bullet fill vector, add texture, set parameters player bullet
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                if(player.getShoot_pattern() == 0){
                    if (delay.getElapsedTime().asMilliseconds()>player.getShoot_fr()) {
                        Bullet bullet(sf::Vector2f((player.getLeft()+player.getRight())/2,(player.getTop()-15)));
                        bullet.setSpeed(-300);
                        bullet.setScale(0.5,0.5);
                        bullet.setDmg(1);
                        bullet.setTexture(*TextureManager::getTexture("LaserG1"));
                        bulletVec.push_back(bullet);
                        delay.restart();
                    }
                }
                else if(player.getShoot_pattern() == 1){
                    if (delay.getElapsedTime().asMilliseconds()>player.getShoot_fr()) {
                        Bullet bullet(sf::Vector2f((player.getLeft()+player.getRight())/2-10,(player.getTop()-15)));
                        Bullet bullet2(sf::Vector2f((player.getLeft()+player.getRight())/2+10,(player.getTop()-15)));
                        bullet.setSpeed(-300);
                        bullet2.setSpeed(-300);
                        bullet.setScale(0.5,0.5);
                        bullet2.setScale(0.5,0.5);
                        bullet.setDmg(1);
                        bullet2.setDmg(1);
                        bullet.setTexture(*TextureManager::getTexture("LaserG1"));
                        bullet2.setTexture(*TextureManager::getTexture("LaserG1"));
                        bulletVec.push_back(bullet);
                        bulletVec.push_back(bullet2);
                        delay.restart();
                    }
                }
                else if(player.getShoot_pattern() == 2){
                    if (delay.getElapsedTime().asMilliseconds()>player.getShoot_fr()) {
                        Bullet bullet(sf::Vector2f((player.getLeft()+player.getRight())/2-10,(player.getTop()-15)));
                        Bullet bullet2(sf::Vector2f((player.getLeft()+player.getRight())/2+10,(player.getTop()-15)));
                        bullet.setSpeed(-300);
                        bullet2.setSpeed(-300);
                        bullet.setScale(0.5,0.5);
                        bullet2.setScale(0.5,0.5);
                        bullet.setDmg(2);
                        bullet2.setDmg(2);
                        bullet.setTexture(*TextureManager::getTexture("LaserG2"));
                        bullet2.setTexture(*TextureManager::getTexture("LaserG2"));
                        bulletVec.push_back(bullet);
                        bulletVec.push_back(bullet2);
                        delay.restart();
                    }
                }
            }

            ////Enemy check collision with bullet, erase bullet, drowing enemy bullet
            for(int i = 0; i < (int)bulletVec.size(); i++){
                for(int k = 0; k < (int)enemyVec.size(); k++){
                        sf::FloatRect bullet = bulletVec[i].getGlobalBounds();
                        if(!enemyVec.empty()){
                            if(enemyVec[k].colision(bullet,bulletVec[i].getDmg()))
                            {
                                bulletVec.erase(bulletVec.begin()+i);
                            }
                        }
                }
            }
            if (delayEnemy.getElapsedTime().asSeconds() > fr*(1.0/enemyVec.size()) && !enemyVec.empty()) {
                int rd = rand()%enemyVec.size();
                Bullet bullet(sf::Vector2f((enemyVec[rd].getLeft()+enemyVec[rd].getRight())/2,(enemyVec[rd].getBottom()+15)));
                bullet.setSpeed(150);
                bullet.setScale(0.5,0.5);
                bullet.setTexture(*TextureManager::getTexture("LaserR"));
                bulletEnemyVec.push_back(bullet);
                delayEnemy.restart();
            }

            ////Drop & enemy erase & enemy fill vector
            for(int i = 0; i < (int)enemyVec.size(); i++){
                    if(enemyVec[i].getHp()<1){
                        if(rand()%10 < 1)
                        {
                            switch(rand()%5+1)
                            {
                                case 1:
                                {
                                    Drop drop(sf::Vector2f(enemyVec[i].getPosition()));
                                    drop.setTexture(*TextureManager::getTexture("Drop1"));
                                    drop.setdrop_number(1);
                                    drop.setScale(0.7,0.7);
                                    dropVec.push_back(drop);
                                    break;
                                }
                                case 2:
                                {
                                    Drop drop(sf::Vector2f(enemyVec[i].getPosition()));
                                    drop.setTexture(*TextureManager::getTexture("Drop2"));
                                    drop.setdrop_number(2);
                                    drop.setScale(0.7,0.7);
                                    dropVec.push_back(drop);
                                    break;
                                }
                                case 3:
                                {
                                    Drop drop(sf::Vector2f(enemyVec[i].getPosition()));
                                    drop.setTexture(*TextureManager::getTexture("Drop3"));
                                    drop.setdrop_number(3);
                                    drop.setScale(0.7,0.7);
                                    dropVec.push_back(drop);
                                    break;
                                }
                                case 4:
                                {
                                    Drop drop(sf::Vector2f(enemyVec[i].getPosition()));
                                    drop.setTexture(*TextureManager::getTexture("Drop4"));
                                    drop.setdrop_number(4);
                                    drop.setScale(0.7,0.7);
                                    dropVec.push_back(drop);
                                    break;
                                }
                                case 5:
                                {
                                    Drop drop(sf::Vector2f(enemyVec[i].getPosition()));
                                    drop.setTexture(*TextureManager::getTexture("Drop5"));
                                    drop.setdrop_number(5);
                                    drop.setScale(0.7,0.7);
                                    dropVec.push_back(drop);
                                    break;
                                }
                            }

                        }
                        player.setPoint(10);
                        enemyVec.erase(enemyVec.begin()+i);
                    }
                }

            for(int i = 0; i < (int)dropVec.size(); i++){
                dropVec[i].animate(elapsed);
                if(dropVec[i].getPosition().y > window.getSize().y){
                    dropVec.erase(dropVec.begin()+i);
                }
            }

            if(enemyVec.empty())
            {
                cycle++;
                fr*=0.7;
                for (int i = 0; i<7; i++)
                {
                        for(int k=0; k<4; k++)
                        {
                        Enemy enemy(sf::Vector2f(((window.getSize().x-7*70)/2)+(i*70),30+k*70));
                        enemy.setHp(cycle*2);
                        enemy.setTexture(*TextureManager::getTexture("Enemy"));
                        enemy.setScale(0.5,0.5);
                        enemyVec.emplace_back(enemy);
                        }
                }
            }

            /////Drop&Player
            for(int i = 0; i < (int)dropVec.size(); i++)
            {
                if(player.collision(dropVec[i].getGlobalBounds()))
                {
                    switch (dropVec[i].getdrop_number())
                    {
                    case 1:
                        if(player.getShoot_pattern() < 2)
                        {
                            player.iShoot_pattern(1);
                        }
                        break;
                    case 2:
                        if(player.getShoot_fr()>30)
                        {
                            player.setShoot_fr(player.getShoot_fr()*0.9);
                        }
                        break;
                    case 3:
                        player.setHp(1);
                        break;
                    case 4:
                        if(player.getSpeed()<450)
                        player.setSpeed(1.1);
                        break;
                    case 5:
                        player.setPoint(100);
                        break;

                    }

                    dropVec.erase(dropVec.begin()+i);

                }
            }

            ////Enemy bullet collision and player collision
            for(int i = 0 ; i < (int)bulletEnemyVec.size() ; i++)
            {
                sf::FloatRect bullet = bulletEnemyVec[i].getGlobalBounds();
                if(player.collision(bullet))
                {
                    player.setHp(-1);
                    bulletEnemyVec.erase(bulletEnemyVec.begin()+i);
                }
            }
            for(int i = 0 ; i < (int)enemyVec.size() ; i++)
            {
                sf::FloatRect enemy = enemyVec[i].getGlobalBounds();
                if(player.collision(enemy))
                {
                    player.setHp(-1);
                    enemyVec.erase(enemyVec.begin()+i);
                }
            }
            ////Score
            scoreText.setString("Score: " +to_string(player.getPoint()));

            ////Health bar
            if(player.getHp()<=5)
            {
                for(int i = 0 ; i < player.getHp() ; i++){
                    sf::Sprite life;
                    life.setTexture(*TextureManager::getTexture("Life"));
                    life.setPosition(5+i*25,5);
                    life.setScale(0.7,0.7);
                    lifeVec.emplace_back(life);
                }
            }
            else if(player.getHp()>5)
            {
                liveText.setString("x " + to_string(player.getHp()));
                lifex.setTexture(*TextureManager::getTexture("Life"));
                lifex.setPosition(5,5);
                lifex.setScale(0.7,0.7);

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
            if(player.getHp()<=5)
                for(int i = 0 ; i < player.getHp() ; i++){
                    window.draw(lifeVec[i]);
                }
            else if(player.getHp()>5)
            {
                window.draw(lifex);
                window.draw(liveText);
            }

            window.draw(player);
            window.draw(scoreText);
            window.display();

        }
        else if(player.getHp() < 1)
        {
            QFile best("Best.txt");
            if (!best.open(QIODevice::ReadOnly))
            {
                std::cout<<"Error";
            }
            line = best.readLine();
            best.close();

            if(line.toInt()<player.getPoint()){
                if (!best.open(QIODevice::WriteOnly))
                {
                    std::cout<<"Error";
                }
                QTextStream out(&best);
                out << player.getPoint();
            }
            best.close();

            if (!best.open(QIODevice::ReadOnly))
            {
                std::cout<<"Error";
            }
            line = best.readLine();

            best.close();
            highScore.setString("High score: "+line.toStdString());
            window.draw(back);
            window.draw(gameover);
            window.draw(highScore);
            window.display();
            best.close();
        }
    }

    return 0;
}
