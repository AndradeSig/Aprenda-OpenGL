all:
	g++ -c source/window.cpp
	g++ window.o -o Executable glad.o -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
	./Executable