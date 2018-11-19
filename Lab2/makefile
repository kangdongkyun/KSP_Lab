TARGET = Lab2_1.out Lab2_2.out Lab2_3.out
OBJS = Lab2_1 Lab2_2 Lab2_3

all: $(TARGET)

CC = gcc

Lab2_1: Lab2_1.c
	$(CC) -o $@ $<
Lab2_2: Lab2_2.c
	$(CC) -o $@ $<
Lab2_3: Lab2_3.c
	$(CC) -o $@ $<

clean: 
	rm -f $(OBJS)
	rm -f $(TARGET)

