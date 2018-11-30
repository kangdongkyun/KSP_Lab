TARGET = 9_1.out 9_2.out 9_3.out
OBJS = 9_1 9_2 9_3

all: $(TARGET)

CC = gcc

9_1: 9_1.c
	$(CC) -o $@ $< -lm
9_2: 9_2.c
	$(CC) -o $@ $< -lm
9_3: 9_3.c
	$(CC) -o $@ $< -lm

clean: 
	rm -f $(OBJS)
	rm -f $(TARGET)

