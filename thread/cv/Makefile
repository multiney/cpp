all:cv

CC=g++
CPPFLAGS=-Wall -std=c++11 -ggdb
LDFLAGS=-pthread

cv:cv.o
	$(CC) $(LDFLAGS) -o $@ $^

cv.o:cv.cc
	$(CC) $(CPPFLAGS) -o $@ -c $^

.PHONY:
	clean

clean:
	rm cv.o cv
