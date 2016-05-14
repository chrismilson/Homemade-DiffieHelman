CC=gcc
CFILES=crypto.c encode.c decode.c matrix.c
OBJECTS=crypto.o encode.o decode.o matrix.o
OUT=crypto

all: $(OBJECTS)
	$(CC) $^ -o $(OUT)

debug: CC += -g
debug: all

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f *.o
	rm -f crypto
