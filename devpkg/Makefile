CC=cc
PREFIX?=/usr/local

IDIR= ./include
CFLAGS=-g -Wall -I$(PREFIX)/apr/include/apr-1 -I$(PREFIX)/apr/include/apr-util-1 -I$(IDIR)
LDFLAGS=-L$(PREFIX)/apr/lib/ -lapr-1 -pthread -laprutil-1

ODIR=obj

D=db.h shell.h commands.h bstrlib.h
DEPS=$(patsubst %, $(IDIR)/%, $(D))

O=bstrlib.o db.o shell.o commands.o
OBJECTS=$(patsubst %, $(ODIR)/%, $(O))

PROGRAM=devpkg

all: $(PROGRAM)

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) $@.c $^ -o $@ $(LDFLAGS)
 
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c $(CFLAGS) $< -o $@ $(LDFLAGS)

install: all
	install -d $(DESTDIR)$(PREFIX)/bin/
	install devpkg $(DESTDIR)$(PREFIX)/bin/


.PHONY: clean
clean:
	rm -f $(OBJECTS)
	rm -f devpkg
	rm -rf *.dSYM
