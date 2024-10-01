# Makefile for your library management system

CXX=g++
CXXFLAGS=-Wall -std=c++11

# Target: main executable
main: main.o Library.o Book.o Journals.o PublicationRank.o User.o functions.o classFunctions.o
	$(CXX) $(CXXFLAGS) main.o Library.o Book.o Journals.o PublicationRank.o User.o functions.o classFunctions.o -o main

# Compile source files into object files
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Library.o: Library.cpp
	$(CXX) $(CXXFLAGS) -c Library.cpp

Book.o: Book.cpp
	$(CXX) $(CXXFLAGS) -c Book.cpp

Journals.o: Journals.cpp
	$(CXX) $(CXXFLAGS) -c Journals.cpp

PublicationRank.o: PublicationRank.cpp
	$(CXX) $(CXXFLAGS) -c PublicationRank.cpp

User.o: User.cpp
	$(CXX) $(CXXFLAGS) -c User.cpp

functions.o: functions.cpp
	$(CXX) $(CXXFLAGS) -c functions.cpp

classFunctions.o: classFunctions.cpp
	$(CXX) $(CXXFLAGS) -c classFunctions.cpp

# Clean up object files and executable
clean:
	rm -f *.o main
