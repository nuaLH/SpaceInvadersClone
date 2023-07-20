all: compile link

compile:
	g++ -c main.cpp Player.cpp Bullet.cpp Enemy.cpp -Iinclude -DSFML_STATIC

link:
	g++ main.o -o main Player.o Bullet.o Enemy.o -Llib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lfreetype -lwinmm -lgdi32 -mwindows -lsfml-main 

clean:
	del *.o
	del main.exe