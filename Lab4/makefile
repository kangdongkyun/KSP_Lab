TARGET = 4_1.out 4_2.out 4_3.out
OBJS = 4_1 4_2 4_3

all: $(TARGET)

CC = gcc

4_1: 4_1.c
	$(CC) -o $@ $<
4_2: 4_2.c
	$(CC) -o $@ $<
4_3: 4_3.c
	$(CC) -o $@ $<

clean: 
	rm -f $(OBJS)
	rm -f $(TARGET)

