poker: misc.o cards.o hands.o deck.o player.o pokerplayer.o pokerplayergroup.o pot.o table.o basegame.o holdemprefloplogic.o holdemui.o preflopgame.o main.o
	g++ misc.o cards.o hands.o deck.o player.o pokerplayer.o pokerplayergroup.o pot.o table.o basegame.o holdemprefloplogic.o holdemui.o preflopgame.o main.o -o poker

misc.o: misc.cpp misc.h
	g++ -std=c++17 -g -O0 -c misc.cpp

cards.o: cards.cpp cards.h
	g++ -std=c++17 -g -O0 -c cards.cpp

hands.o: hands.cpp hands.h
	g++ -std=c++17 -g -O0 -c hands.cpp

deck.o: deck.cpp deck.h
	g++ -std=c++17 -g -O0 -c deck.cpp

player.o: player.cpp player.h
	g++ -std=c++17 -g -O0 -c player.cpp

pokerplayer.o: pokerplayer.cpp pokerplayer.h
	g++ -std=c++17 -g -O0 -c pokerplayer.cpp

pokerplayergroup.o: pokerplayergroup.cpp pokerplayergroup.h
	g++ -std=c++17 -g -O0 -c pokerplayergroup.cpp

pot.o: pot.cpp pot.h
	g++ -std=c++17 -g -O0 -c pot.cpp

table.o: table.cpp table.h
	g++ -std=c++17 -g -O0 -c table.cpp

basegame.o: basegame.cpp basegame.h
	g++ -std=c++17 -g -O0 -c basegame.cpp

holdemprefloplogic.o: holdemprefloplogic.cpp holdemprefloplogic.h
	g++ -std=c++17 -g -O0 -c holdemprefloplogic.cpp

holdemui.o: holdemui.cpp holdemui.h
	g++ -std=c++17 -g -O0 -c holdemui.cpp

preflopgame.o: preflopgame.cpp preflopgame.h
	g++ -std=c++17 -g -O0 -c preflopgame.cpp

main.o: main.cpp
	g++ -std=c++17 -g -O0 -c main.cpp
	
clean:
	del *.o poker.exe
