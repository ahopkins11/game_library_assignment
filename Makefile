# Makefile for Game Library
 
CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++11
 
TARGET  = game_library
OBJS    = main.o game.o library.o
 
# Link executable from object files
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
 
# Compile each source file into an object file
main.o: main.cpp game.h library.h
	$(CXX) $(CXXFLAGS) -c main.cpp
 
game.o: game.cpp game.h
	$(CXX) $(CXXFLAGS) -c game.cpp
 
library.o: library.cpp library.h game.h
	$(CXX) $(CXXFLAGS) -c library.cpp
 
# Remove compiled files
clean:
	rm -f $(OBJS) $(TARGET)
