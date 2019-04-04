CC=g++
LN=g++
CXXFLAGS = -std=c++11

All : main

main : main.o utils.o patterns.o
	@echo "compiling and linking the code"
	@echo "running the program, usage: ./solution"
	$(LN) -o solution main.o utils.o patterns.o
	./solution

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $<









