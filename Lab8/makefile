TARGET = 8_1.out 8_2.out 8_3.out
OBJS = 8_1 8_2 8_3

all: $(TARGET)

CC = gcc

8_1: 8_1.c
	$(CC) -o $@ $< -lm
8_2: 8_2.c
	$(CC) -o $@ $< -lm
8_4: 8_4.c
	$(CC) -o $@ $< -lm

clean: 
	rm -f $(OBJS)
	rm -f $(TARGET)

