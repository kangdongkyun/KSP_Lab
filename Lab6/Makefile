CC = gcc
# CC = ${GCC}/install/bin/gcc;
CFLAGS = -O3 -Wall -Wno-unused-result -mfma -mavx
OBJS1 = 6_1.o
OBJS2 = 6_2.o
TARGET1 = 6_1.out
TARGET2 = 6_2.out
.SUFFIXES : .c .o

all : $(TARGET1) $(TARGET2)

$(TARGET1): $(OBJS1)
	$(CC) -o $@ $(OBJS1)

$(TARGET2): $(OBJS2)
	$(CC) -o $@ $(OBJS2)

clean:
	rm -rf $(OBJS1) $(TARGET1)
	rm -rf $(OBJS2) $(TARGET2)
