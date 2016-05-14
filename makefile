CC=gcc
CFILES=main.c encode.c decode.c matrix.c
OBJECTS=main.o encode.o decode.o matrix.o
OUT=main

all: $(OBJECTS)
	$(CC) $^ -o $(OUT)

debug: CC += -g
debug: all

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f *.o
	rm -f main
