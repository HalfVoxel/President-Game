
UNAME := $(shell uname)

all:
	mkdir -p bin
ifeq ($(UNAME),Darwin)
	clang++ -std=c++11 -stdlib=libc++ bots/*.cpp game.cpp -g -O2 -Wall -o bin/game
else
	Might use incorrect arguments
	g++ -std=c++11 -stdlib=libc++ bots/*.cpp game.cpp -g -O2 -Wall -o bin/game
endif

