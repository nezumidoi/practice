CC=gcc
CFLAGS=-Wall -O2
OBJS=server.o
TARGET=server

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm $(TARGET) $(OBJS)

