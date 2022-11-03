all:mutex

CC=g++
CPPFLAGS=-Wall -std=c++11 -ggdb
LDFLAGGS=-pthread

mutex: mutex.o
	$(CC) $(LDFLAGGS) -o $@ $^

mutex.o: mutex.cc
	$(CC) $(CPPFLAGS) -o $@ -c $^

.PHONY:
	clean

clean:
	rm mutex.o mutex
