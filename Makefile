poker: cards.o hands.o main.o
	g++ cards.o hands.o main.o -o poker

cards.o: cards.cpp cards.h
	g++ -std=c++17 -c cards.cpp

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

hands.o: hands.cpp hands.h
	g++ -std=c++17 -c hands.cpp
	
clean:
	del *.o poker.exe
