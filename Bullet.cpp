#include <SFML/Graphics.hpp>
#include <vector>
#include <iterator>
#include "Bullet.h"
#include "Global.h"

using namespace sf;
using namespace std;

Bullet::Bullet(Vector2f size){
    bullet.setSize(size);
}

void Bullet::fire(short speed){
    bullet.move(0,-speed);
}

//get values of bullet location
int Bullet::getRight(){
    return bullet.getPosition().x + bullet.getSize().x;
}

int Bullet::getLeft(){
    return bullet.getPosition().x;
}

int Bullet::getTop(){
    return bullet.getPosition().y;
}

int Bullet::getBot(){
    return bullet.getPosition().y + bullet.getSize().y;
}

void Bullet::draw(RenderWindow &bwindow){
    bwindow.draw(bullet);
}

void Bullet::setPos(Vector2f newPos){
    bullet.setPosition(newPos);
}


