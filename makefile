# Makefile
CXX_FLAG = --std=c++17 -g

project1: project1.o
	g++ $(CXX_FLAG) project1.o -o project1.out

project1.o: project1.cpp
	g++ -c $(CXX_FLAG) project1.cpp

clean:
	rm -f project1 *.o
