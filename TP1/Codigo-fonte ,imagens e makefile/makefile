install:	
	sudo apt-get update
	sudo apt-get install freeglut3 freeglut3-dev binutils-gold g++ cmake libglew-dev mesa-common-dev libglew1.5-dev libglm-dev
	sudo apt-get install libsoil-dev
	sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
game:	 
	gcc -o Jogo.exe main.c desenha.c menuPrincipal.c texto.c -lSOIL -lglut -lGLU -lGL -lm -lSDL -lSDL_mixer
run:	Jogo.exe
	./Jogo.exe

