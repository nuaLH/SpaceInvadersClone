#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Global.h"

using namespace sf;
using namespace std;

Player::Player(string imgDirectory){
    texture.loadFromFile(imgDirectory);
    player.setTexture(texture);
    
}

void Player::setPos(){
    x = 0.5f * (screen_width - base_size);
	y = screen_height - 2 * base_size;
    player.setPosition(x,y);
}

void Player::draw(RenderWindow  &pwindow){
    pwindow.draw(player);
    
}

int Player::getHp(){
    return hp;
}
int Player::getHpMax(){
    return hpMax;
}
void Player::setHp(int hpp){
    hp = hpp;
}
void Player::loseHp(int value){
    hp -= value;
    if(hp < 0){
        hp = 0;
    }
}

void Player::move(int direction){
    if(direction == 0){
        player.move(-player_speed, 0);
    } else if(direction == 1){
        player.move(player_speed, 0);
    }
}
//values for player pos
int Player::getX(){
    return player.getPosition().x;
}

int Player::getY(){
    return player.getPosition().y;
}

//cooldown for shooting so it doesnt spam
void Player::atkupdate(){
    if(atkCooldown<atkCooldownMax){
        atkCooldown+=0.5f;
    }
}
const bool Player::canatk(){
    if(atkCooldown>=atkCooldownMax){
        atkCooldown=0.f;
        return true;
    }
    return false;
}

