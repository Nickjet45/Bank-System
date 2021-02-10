main.exe : main.o Banking.o
	g++ -Wall main.o -c main.exe

main.o : main.cpp Banking.hpp
	g++ -Wall -c main.cpp

Banking.o: Banking.hpp Banking.cpp
	g++ -Wall -c Banking.cpp


clean : 
	rm *.o