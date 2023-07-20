#include <SFML/Graphics.hpp>
#include "Bullet.h"
using namespace sf;
using namespace std;

class Enemy{

    Texture texture;
    Sprite enemy;
    int x,y;
    int i = 0;
    double point = 100;
    float spawnCooldown = 0.f;
    float spawnCooldownMax = 25.f;
    float enemy_speed = 2.f;
    public:
        Enemy(string imgDirectory);
        void draw(RenderWindow  &window);
        int getX();
        int getY();
        void move(int direction);
        void checkCol(Bullet bullet);
        const bool canmove();
        void spawnupdate();
        const bool canspawn();
        void setPos(int x, int y);
        int getBot();
        int getTop();
        const double& getPoints() const;
};