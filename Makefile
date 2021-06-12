run_server:
	g++ -I./include -Wall -std=c++11 -g src/server.c src/socket_utils.c -o server

run_client:
	g++ -I./include -Wall -std=c++11 -g src/client.c src/socket_utils.c -o client