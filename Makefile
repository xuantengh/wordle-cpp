# WORDLE game written in cpp

FMT_LINK_ARGS := $(shell pkg-config --libs --cflags fmt)

all: wordle

wordle: game.o main.o
	g++ $(FMT_LINK_ARGS) $^ -o $@

game.o: src/game.cc include/game.h
	g++ $(USER_DEFINED) -c -Iinclude $(FMT_LINK_ARGS) $< -o $@

main.o: src/main.cc
	g++ -c -Iinclude -o $@ $<

clean:
	rm -f *.o wordle