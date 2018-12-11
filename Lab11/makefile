TARGET = 11_1(a).out 11_2_revMsg.out 11_2_sendMsg.out
OBJS = 11_1(a) 11_2_revMsg 11_2_sendMsg

all: $(TARGET)

CC = gcc

11_1: 11_1(a).c
	$(CC) -o $@ $< -lm
11_2_revMsg: 11_2_revMsg.c
	$(CC) -o $@ $< -lm
11_2_sendMsg: 11_2_sendMsg.c
	$(CC) -o $@ $< -lm

clean: 
	rm -f $(OBJS)
	rm -f $(TARGET)

