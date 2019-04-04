# DIP Homework Assignment #2 # March 27, 2019
# Name: 陳偉
# ID #: R06944043
# email: r06944043@ntu.edu.tw
# compiled on macOS Mojave with g++
# define your compiler and linker 
CC=g++
LN=g++
CXXFLAGS = -std=c++11

All : prob1 

prob1 : problem_1.o utils.o patterns.o
	@echo "Problem 1"
	@echo "compiling and linking the code"
	@echo "running the program, usage: "
	$(LN) -o solution1 problem_1.o utils.o patterns.o
	./solution1 

# prob2 : problem_2.o utils.o
# 	@echo "\nProblem 2"
# 	@echo "compiling and linking the code"
# 	@echo "running the program, usage: ./solution2 inputImageName"
# 	@echo "output: C.raw"
# 	$(LN) -o solution2 problem_2.o utils.o
# 	./solution2 ../raw/sample4.raw

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $<









