CXX = g++
CXXFLAGS = -std=c++0x -Wall -g

all: main.o Document.o Editor.o
	$(CXX) $(CXXFLAGS) main.o Document.o Editor.o
	./a.out  < ./data/input.txt
	
Document.o: Document.cpp Document.h
	$(CXX) $(CXXFLAGS) -c Document.cpp -o Document.o

Player.o: Editor.cpp Editor.h
	$(CXX) $(CXXFLAGS) -c Editor.cpp -o Editor.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

clean:
	rm *.o a.out
