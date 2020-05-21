BIN=mazegen
CC=g++
CFLAGS= -std=c++14 -g
DEPEND= main.o Terminal.o

all: $(BIN)

$(BIN): $(DEPEND)
	$(CC) $(CFLAGS) $(DEPEND) -o $(BIN) -lncurses

main.o: main.cpp Terminal.hpp
	$(CC) main.cpp -c

Terminal.o: Terminal.cpp Terminal.hpp
	$(CC) Terminal.cpp -c

run: all
	./$(BIN)

memcheck: all
	valgrind ./$(BIN) -v

clean:
	rm -rf *.o
	rm -rf $(BIN)
