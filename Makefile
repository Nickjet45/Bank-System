CXX = g++
CXXFLAGS = -Wall

main.exe : main.o Banking.o
	$(CXX) $(CXXFLAGS) -o $@ $^


clean : 
	rm *.o