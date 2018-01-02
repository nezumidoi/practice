CC=gcc
CFLAGS=-Wall -O2
OBJS=sender.o
TARGET=sender

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

.PHONY: clean
clean:
	rm $(TARGET) $(OBJS)

