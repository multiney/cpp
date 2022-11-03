all:result

CC=g++
CPPFLAGS=-Wall -std=c++11 -ggdb

result:result.o
	$(CC) -o $@ $^

result.o:result.cc
	$(CC) $(CPPFLAGS) -o $@ -c $^

.PHONY:
	clean

clean:
	rm result.o result
