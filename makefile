CC=gcc

all:
	$(CC) main.c encode.c aes/matrix.c -o main
