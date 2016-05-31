#rshell makefile

COMPILE = g++
OBJS = src/Format.cpp src/Command.cpp src/Test.cpp src/Base.h
FLAGS = -Wall -Werror -ansi -pedantic


all:

	mkdir -p bin
	$(COMPILE) $(FLAGS) src/main.cpp $(OBJS) -o bin/rshell

clean:
	rm bin/rshell
	rm -rf bin
