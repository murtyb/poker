CC = g++
CFLAGS = -std=c++17 -g -O0 -c
OBJS = misc.o cards.o hands.o deck.o player.o pokerplayer.o pokerplayergroup.o pot.o table.o basegame.o holdemprefloplogic.o holdemui.o preflopgame.o main.o
PROGNAME = poker

poker: $(OBJS)
	$(CC) $(OBJS) -o $(PROGNAME)

%.o: %.cpp
	$(CC) $(CFLAGS) $<

#Dependency chains:
cards.o                  : cards.cpp cards.h
misc.o                   : misc.cpp misc.h
hands.o                  : hands.cpp hands.h
deck.o                   : deck.cpp deck.h
player.o                 : player.cpp player.h
pokerplayer.o            : pokerplayer.cpp pokerplayer.h
pokerplayergroup.o       : pokerplayergroup.cpp pokerplayergroup.h
pot.o                    : pot.cpp pot.h
table.o                  : table.cpp table.h
basegame.o               : basegame.cpp basegame.h
holdemprefloplogic.o     : holdemprefloplogic.cpp holdemprefloplogic.h
holdemui.o               : holdemui.cpp holdemui.h
preflopgame.o            : preflopgame.cpp preflopgame.h
main.o                   : main.cpp

clean:
	del *.o poker.exe