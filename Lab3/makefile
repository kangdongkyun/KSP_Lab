CFLAGS= -g -Wall
TARGET = 3_1.out 3_2.out 3_3.out
SRCS = 3_1.c 3_2.c 3_3.c
OBJS = 3_1.o 3_2.o 3_3.o

all : $(TARGET)

CC = gcc

3_1.out : 3_1.o
	$(CC) -o 3_1.out 3_1.o

3_2.out : 3_2.o
	$(CC) -o 3_2.out 3_2.o

3_3.out : 3_3.o
	$(CC) -o 3_3.out 3_3.o

3_1.o: 3_1.c
	$(CC) -c $(CFLAGS) 3_1.c

3_2.o: 3_2.c
	$(CC) -c $(CFLAGS) 3_2.c

3_3.o: 3_3.c
	$(CC) -c $(CFLAGS) 3_3.c



clean:
	rm -f *.o
	rm -f $(TARGET)

