poker: cards.o hands.o deck.o main.o
	g++ cards.o hands.o deck.o main.o -o poker

cards.o: cards.cpp cards.h
	g++ -std=c++17 -c cards.cpp

hands.o: hands.cpp hands.h
	g++ -std=c++17 -c hands.cpp

deck.o: deck.cpp deck.h
	g++ -std=c++17 -c deck.cpp

main.o: main.cpp
	g++ -std=c++17 -c main.cpp
	
clean:
	del *.o poker.exe
