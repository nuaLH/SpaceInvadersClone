#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;



class Bullet{
    RectangleShape bullet;
    bool dead;
    public:
        
        Bullet(Vector2f size);
        void fire(short speed);
        int getRight();
        int getLeft();
        int getTop();
        int getBot();
        void draw(RenderWindow &bwindow);
        void setPos(Vector2f newPos);
};
