#include <SFML/Graphics.hpp>
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>

#include "Player.h"
#include "Global.h"
#include "Enemy.h"

using namespace sf;
using namespace std;

int main(){
    
    //creating window and resizing
    RenderWindow window(VideoMode(resize * screen_width, resize * screen_height), "Galaga Invaders", Style::Close);
	window.setView(View(FloatRect(0, 0, screen_width, screen_height)));

    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);

    Texture backgroundTexture;
    Sprite background;

    //loads background
    backgroundTexture.loadFromFile("images/background.jpg");
    background.setTexture(backgroundTexture);

    //loads player
    Player player("images/ship.png");
    player.setPos();

    //loads enemy
    vector<Enemy> enemies;
    Enemy enemy("images/enemy");
    
    //bullets
    vector<Bullet> bulletVec;
    bool isFiring = false;
    
    //GUI
    //Point System
    Font font;
    Text pointTxt;
    font.loadFromFile("images/ARCADE_I.ttf");
    pointTxt.setFont(font);
    pointTxt.setCharacterSize(12);
    pointTxt.setFillColor(Color::White);
    pointTxt.setPosition(2,0);
    int points = 0;

    //Title Screen
    Text titleScreen;
    titleScreen.setFont(font);
    titleScreen.setCharacterSize(30);
    titleScreen.setFillColor(Color::Green);
    titleScreen.setString("Space\nInvaders");
    titleScreen.setPosition(screen_width/2 - titleScreen.getGlobalBounds().width / 2, screen_height / 2 - titleScreen.getGlobalBounds().height / 2 - 10);
    bool enter = false;

    Text enterTxt;
    enterTxt.setFont(font);
    enterTxt.setCharacterSize(12);
    enterTxt.setFillColor(Color::White);
    enterTxt.setString("Press Enter to Start");
    enterTxt.setPosition(screen_width/2 - enterTxt.getGlobalBounds().width / 2, screen_height / 2 + 40);


    //Game Over Screen
    Text gameOverTxt;
    gameOverTxt.setFont(font);
    gameOverTxt.setCharacterSize(30);
    gameOverTxt.setFillColor(Color::Red);
    gameOverTxt.setString("Game Over");
    gameOverTxt.setPosition(screen_width/2 - gameOverTxt.getGlobalBounds().width / 2, screen_height / 2 - gameOverTxt.getGlobalBounds().height / 2);

    Text restart;
    restart.setFont(font);
    restart.setCharacterSize(12);
    restart.setFillColor(Color::White);
    restart.setString("Press R to restart");
    restart.setPosition(screen_width/2 - restart.getGlobalBounds().width / 2, screen_height / 2 + 30);

    //HP Bar
    RectangleShape playerHpBar;
    RectangleShape playerHpBarBack;
    playerHpBar.setSize(Vector2f(100.f,10.f));
    playerHpBar.setFillColor(Color::Red);
    playerHpBar.setPosition(Vector2f(2.f,168.f));

    playerHpBarBack = playerHpBar;
    playerHpBarBack.setFillColor(Color(25,25,25,200));

    //while game is open
    while(window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::R)){
                player.setHp(10);
                enemies.clear();
                player.setPos();
                points = 0;

        }
        if (enter == false){
            window.draw(titleScreen);
            window.draw(enterTxt);
            if(Keyboard::isKeyPressed(Keyboard::Enter)){
                enter = true;   
            }
        }
        //game runs if Hp isn't 0
        if(player.getHp() > 0 && enter == true){
            //movement and shooting
            if(Keyboard::isKeyPressed(Keyboard::A) && player.getX() > 0){
                player.move(0);
            }else if(Keyboard::isKeyPressed(Keyboard::D)&& player.getX() < screen_width - base_size){
                player.move(1);
            }
            if(Keyboard::isKeyPressed(Keyboard::Space) && player.canatk()){
                isFiring = true;
            }

            window.clear();

            window.draw(background);

        
            //fires bullet
            if (isFiring == true){
                Bullet newBullet(Vector2f(1,5));
                newBullet.setPos(Vector2f(player.getX()+base_size/2,player.getY()));
                bulletVec.push_back(newBullet);
                isFiring = false;
            }
            for (int i = 0; i < bulletVec.size(); i++){
                bulletVec[i].draw(window);
                bulletVec[i].fire(bullet_speed);
            }
            
            //delete bullets outside of view and erases 
            for (int i = 0; i < bulletVec.size(); i++){
                if (bulletVec[i].getBot() < 0.f){
                    bulletVec.erase(bulletVec.begin() + i);
                }
            }

            //spawn enemy
            if (enemy.canspawn() == true){
                enemy.setPos(rand()%(screen_width-base_size), 0);
                enemies.push_back(enemy);
            }
            for (int i = 0; i < enemies.size(); i++){
                enemies[i].draw(window);
            }
            //enemy movement and death
            for (int i = 0; i < enemies.size(); ++i){
                bool kill = false;
                enemies[i].move(0);

                //detect bullet collision
                for(int j = 0; j < bulletVec.size() && !kill; j++){
                    if (bulletVec[j].getTop() < enemies[i].getBot() && bulletVec[j].getLeft() >= enemies[i].getX() && bulletVec[j].getRight() <= enemies[i].getX() + base_size){
                        points+=enemies[i].getPoints();
                        bulletVec.erase(bulletVec.begin() + j);
                        enemies.erase(enemies.begin() + i);
                        kill = true;
                        
                    }
                }
                //detect if enemy went pass player
                if(!kill){
                    if(enemies[i].getY() > screen_height){
                        player.loseHp(1);
                        enemies.erase(enemies.begin() + i);
                        kill = true;
                    }
                }
                //player collision
                if (player.getX() + base_size/2 >= enemies[i].getX() &&  player.getX() + base_size/2 
                <= enemies[i].getX() + base_size && enemies[i].getBot() >= player.getY() && 
                enemies[i].getTop() < player.getY() + base_size){
                    player.loseHp(10);
                }
                
            }
            //updates Hp Bar
            float hpPercent = static_cast<float>(player.getHp())/player.getHpMax();
            playerHpBar.setSize(Vector2f(100.f*hpPercent,playerHpBar.getSize().y));
            
            
            //updates point system
            stringstream ss;
            ss << points;
            pointTxt.setString(ss.str());

            //cooldowms
            enemy.spawnupdate();
            player.atkupdate();

            //displays stuff
            player.draw(window);
            window.draw(pointTxt);
            window.draw(playerHpBarBack);
            window.draw(playerHpBar);
        }
        if (player.getHp()<=0){
            window.draw(gameOverTxt);
            window.draw(restart);
        }
        window.display();
    } 
    return 0;
}