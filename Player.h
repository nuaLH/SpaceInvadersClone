#ifndef PLAYER_H
#define PLAYER_H

using namespace sf;
using namespace std;

class Player{
    Texture texture;
    Sprite player;

    int x;
    int y;
    int i = 0;
    int hpMax = 10;
    int hp = hpMax;
    float atkCooldown = 0.f;
    float atkCooldownMax = 10.f;

    public:
        Player();
        Player(string imgDirectory);
        void draw(RenderWindow  &pwindow);
        void move(int direction);
        int getX();
        int getY();
        void atkupdate();
        const bool canatk();
        int getHp();
        int getHpMax();
        void setHp(int hpp);
        void loseHp(int value);
        void setPos();
};

#endif