CC=gcc
CFLAGS=-Wall -O2
OBJS=reciever.o
TARGET=reciever

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

.PHONY: clean
clean:
	rm $(TARGET) $(OBJS)

