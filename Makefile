poker: misc.o cards.o hands.o deck.o player.o pot.o game.o simple_game. o main.o
	g++ misc.o cards.o hands.o deck.o player.o pot.o game.o simple_game. o main.o -o poker

misc.o: misc.cpp misc.h
	g++ -std=c++17 -c misc.cpp

cards.o: cards.cpp cards.h
	g++ -std=c++17 -c cards.cpp

hands.o: hands.cpp hands.h
	g++ -std=c++17 -c hands.cpp

deck.o: deck.cpp deck.h
	g++ -std=c++17 -c deck.cpp

player.o: player.cpp player.h
	g++ -std=c++17 -c player.cpp

pot.o: pot.cpp pot.h
	g++ -std=c++17 -c pot.cpp

game.o: game.cpp game.h
	g++ -std=c++17 -c game.cpp

simple_game.o: simple_game.cpp simple_game.h
	g++ -std=c++17 -c simple_game.cpp

main.o: main.cpp
	g++ -std=c++17 -c main.cpp
	
clean:
	del *.o poker.exe
