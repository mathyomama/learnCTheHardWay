CFLAGS = -Wall -g -Q
CC = gcc
OBJECTS = ex22_main ex22.o


all: ex22_main

ex22_main: ex22.o


.PHONY: clean
clean:
	rm -f $(OBJECTS)
