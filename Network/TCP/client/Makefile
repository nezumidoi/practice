CC=gcc
CFLAGS=-Wall -O2
OBJS=client.o
TARGET=client

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

.PHONY: clean
	rm $(TARGET) $(OBJS)

