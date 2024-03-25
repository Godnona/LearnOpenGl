all:
	g++ -I./openGl -I./openGl/include -L./openGl -L./openGl/lib src/main.cpp src/glad.c -L./build -lglfw3dll -o build/main.exe