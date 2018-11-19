TARGET = 7_1.out 7_1_2.out 7_2.out 7_3.out
OBJS = 7_1 7_1_2 7_2 7_3

all: $(TARGET)

CC = gcc

7_1: 7_1.c
	$(CC) -o $@ $< -lm
7_1_2: 7_1_2.c
	$(CC) -o $@ $< -lm
7_2: 7_2.c
	$(CC) -o $@ $< -lm
7_3: 7_3.c
	$(CC) -o $@ $< -lm

clean: 
	rm -f $(OBJS)
	rm -f $(TARGET)

