all:future

CC=g++
CPPFLAGS=-Wall -std=c++11 -ggdb
LDFLAGS=-pthread

future:future.o
	$(CC) $(LDFLAGS) -o $@ $^

future.o:future.cc
	$(CC) $(CPPFLAGS) -o $@ -c $^

.PHONY:
	clean

clean:
	rm future.o future
