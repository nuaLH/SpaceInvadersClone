Using VSCODE (you might need to download SFML if it doesn't work)
make
.\main

ubuntu/Linux
sudo apt-get install libsfml-dev
g++ -c main.cpp Player.cpp Bullet.cpp Enemy.cpp -Iinclude -DSFML_STATIC
g++ main.o -o main Player.o Bullet.o Enemy.o -lsfml-graphics -lsfml-window -lsfml-system
./main

Instructions:
A - Move Left
D - Move Right
Space - Shoot
R - Restart