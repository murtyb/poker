poker: cards.o main.o
	g++ cards.o main.o -o poker

cards.o: cards.cpp cards.h
	g++ -std=c++17 -c cards.cpp

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

clean:
	del *.o poker.exe
