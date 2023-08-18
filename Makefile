All : queue_gl slow_gl X11

queue_gl : ./Thread/gl.cpp ./Thread/numbers.cpp
	g++ ./Thread/gl.cpp -pthread -o ./Executables/queue -lGL -lglut -lGLU

slow_gl : ./Slow/gl.cpp ./Slow/numbers.cpp
	g++ ./Slow/gl.cpp -o ./Executables/slow -lGL -lglut -lGLU

X11 : ./X11/display.cpp ./X11/numbers.cpp
	g++ -w  ./X11/display.cpp -o ./Executables/click -lX11

