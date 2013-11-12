LD_LIBRARY_PATH="./libs"
all: libraries test_stuff

libraries: calc controller timer network cbuffer structure draw menu editor graphics jukebox 

test_stuff: server client

debug: all debug_network

network: ../src/includes/network/udp_protocol.c
	gcc -fPIC -O0 -ggdb -c -o ./libs/libudp_protocol.o ../src/includes/network/udp_protocol.c
	gcc -fPIC -O0 -ggdb -shared -o ./libs/libudp_protocol.so ./libs/libudp_protocol.o

debug_network: ../src/includes/network/udp_protocol.c
	gcc -fPIC -O0 -ggdb -D _DEBUG_ -c -o ./libs/libudp_protocol.o ../src/includes/network/udp_protocol.c
	gcc -fPIC -O0 -ggdb -shared -o ./libs/libudp_protocol.so ./libs/libudp_protocol.o

controller: ../src/includes/player/controller.c
	gcc -fPIC -O0 -ggdb -c -o ./libs/libcontroller.o ../src/includes/player/controller.c
	gcc -fPIC -O0 -ggdb -shared -L./libs -lcalc -o ./libs/libcontroller.so ./libs/libcontroller.o

calc: ../src/includes/calc.c
	gcc -fPIC -O0 -ggdb -c -o ./libs/libcalc.o  ../src/includes/calc.c 
	gcc -fPIC -O0 -ggdb -shared -o ./libs/libcalc.so ./libs/libcalc.o

timer: ../src/includes/graphics/timer.c
	gcc -fPIC -O0 -ggdb -c  -o ./libs/libtimer.o ../src/includes/graphics/timer.c 	
	gcc -fPIC -O0 -ggdb -shared -o ./libs/libtimer.so ./libs/libtimer.o  -lSDL

menu: ../src/includes/graphics/menu.c
	gcc -fPIC -O0 -ggdb -c  -o ./libs/libmenu.o ../src/includes/graphics/menu.c 
	gcc -fPIC -O0 -ggdb -shared -o ./libs/libmenu.so ./libs/libmenu.o -L./libs -lcalc -ldraw -lSDL -lSDL_image -lGL

structure: ../src/includes/graphics/structure.c
	gcc -fPIC -O0 -ggdb -c  -o ./libs/libstructure.o ../src/includes/graphics/structure.c 	
	gcc -fPIC -O0 -ggdb -shared -o ./libs/libstructure.so ./libs/libstructure.o

draw: ../src/includes/graphics/draw.c
	gcc -fPIC -O0 -ggdb -c  -o ./libs/libdraw.o ../src/includes/graphics/draw.c
	gcc -fPIC -O0 -ggdb -shared -o ./libs/libdraw.so ./libs/libdraw.o -L./libs -lstructure -lcalc -lSDL -lSDL_image -lGL

graphics: ../src/includes/graphics.c
	gcc -fPIC -O0 -ggdb -c  -o ./libs/libgraphics.o ../src/includes/graphics.c
	gcc -fPIC -O0 -ggdb -shared -o ./libs/libgraphics.so ./libs/libgraphics.o -lSDL -lSDL_image -lSDLmain -lGL -L./libs -ltimer -ldraw  -lstructure -lmenu -lcalc -leditor

editor: ../src/includes/graphics/editor.c
	gcc -fPIC -O0 -ggdb -c  -o ./libs/libeditor.o ../src/includes/graphics/editor.c
	gcc -fPIC -O0 -ggdb -shared -o ./libs/libeditor.so ./libs/libeditor.o
	
cbuffer: ../src/includes/cbuffer.c
	gcc -fPIC -O0 -ggdb -c  -o ./libs/libcbuffer.o ../src/includes/cbuffer.c
	gcc -fPIC -O0 -ggdb -shared -o ./libs/libcbuffer.so ./libs/libcbuffer.o

jukebox: ../src/includes/jukebox.c
	gcc -fPIC -O0 -ggdb -c  -o ./libs/libjukebox.o ../src/includes/jukebox.c
	gcc -fPIC -O0 -ggdb -shared -o ./libs/libjukebox.so ./libs/libjukebox.o


client: ../src/client.c
	gcc -fPIC -O0 -ggdb -o ./bins/client ../src/client.c  -L./libs -ludp_protocol -ltimer -ldraw -lgraphics -lcbuffer -ldraw -leditor -lmenu -lstructure -ljukebox -lSDL -lSDLmain -lSDL_mixer
	paxctl -m ./bins/client

server: ../src/server.c
	gcc -fPIC -O0 -ggdb -o ./bins/server ../src/server.c -L./libs -ludp_protocol -lcontroller -lcalc -lcbuffer -ltimer -lstructure -lSDLmain -lSDL
	paxctl -m ./bins/server

clean:
	rm ./libs/*.so
	rm ./libs/*.o
	rm ./bins/client
	rm ./bins/server
