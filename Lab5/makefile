TARGET = 5_1.out 5_2.out getGrade.out
OBJS = 5_1 5_2 getGrade

all: $(TARGET)

CC = gcc

5_1: 5_1.c
	$(CC) -o $@ $<
5_2: 5_2.c
	$(CC) -o $@ $<
getGrade: getGrade.c
	$(CC) -o $@ $<

clean: 
	rm -f $(OBJS)
	rm -f $(TARGET)

