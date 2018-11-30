TARGET = 10_1.out server.out client.out
OBJS = 10_1 server client

all: $(TARGET)

CC = gcc

10_1: 10_1.c
	$(CC) -o $@ $< -lm
server: server.c
	$(CC) -o $@ $< -lm
client: client.c
	$(CC) -o $@ $< -lm

clean: 
	rm -f $(OBJS)
	rm -f $(TARGET)

