#include <SFML/Graphics.hpp>
#include <vector>
#include <iterator>
#include <stdlib.h>

#include "Enemy.h"
#include "Global.h"


using namespace sf;
using namespace std;

Enemy::Enemy(string imgDirectory){
    
    texture.loadFromFile("images/enemy.png");
    enemy.setTexture(texture);
}

void Enemy::setPos(int x, int y){
    enemy.setPosition(x,y);
}

void Enemy::draw(RenderWindow  &window){
    window.draw(enemy);
}


void Enemy::move(int direction){
    if(direction == 0){
        enemy.move(0,1.f);
    } if(direction == 1){
        enemy.move(0,0.5f);
    }
}
//position of enemy
int Enemy::getX(){
    return enemy.getPosition().x;
} 
int Enemy::getY(){
    return enemy.getPosition().y;
} 
int Enemy::getTop(){
    return enemy.getPosition().y;
}
int Enemy::getBot(){
    return enemy.getPosition().y + base_size;
}


//spawn enemies
void Enemy::spawnupdate(){
    if(spawnCooldown<spawnCooldownMax){
        spawnCooldown+=0.5f;
    }
}
const bool Enemy::canspawn(){
    if(spawnCooldown>=spawnCooldownMax){
        spawnCooldown=0.f;
        return true;
    }
    return false;
}

const double & Enemy::getPoints() const{
    return point;
}