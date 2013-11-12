all: calc controller linkedlist network server client 

libraries: calc controller linkedlist network

test_stuff: server client

network: ../src/includes/network/udp_protocol.c
	gcc -O0 -ggdb -c -fPIC -o libudp_protocol.o ../src/includes/network/udp_protocol.c
	gcc -O0 -ggdb -fPIC -shared -o libudp_protocol.so libudp_protocol.o 

controller: ../src/includes/player/controller.c
	gcc -O0 -ggdb -c -fPIC -o libcontroller.o ../src/includes/player/controller.c
	gcc -O0 -ggdb -fPIC -shared -o libcontroller.so libcontroller.o
linkedlist: ../src/includes/linkedList.c
	gcc -O0 -ggdb -c -fPIC -o liblinkedlist.o ../src/includes/linkedList.c
	gcc -O0 -ggdb -fPIC -shared -o liblinkedlist.so liblinkedlist.o

calc: ../src/includes/libcalc.c
	gcc -O0 -ggdb -c -fPIC -o libcalc.o  ../src/includes/libcalc.c
	gcc -O0 -ggdb -fPIC -shared -o libcalc.so libcalc.o

linkedlist: ../src/includes/linkedList.c
	gcc -O0 -ggdb -c -fPIC -o liblinkedlist.o ../src/includes/linkedList.c
	gcc -O0 -ggdb -fPIC -shared -o liblinkedlist.so liblinkedlist.o

client: ../src/client.c
	gcc -O0 -ggdb -o client ../src/client.c -L . -ludp_protocol
#	paxctl -m client

server: ../src/server.c
	gcc -O0 -ggdb -o server ../src/server.c -L . -ludp_protocol -lcontroller -lcalc -llinkedlist -lSDL
#	paxctl -m server

clean:
	rm ./client
	rm ./server
	rm ./*.so
	rm ./*.o
