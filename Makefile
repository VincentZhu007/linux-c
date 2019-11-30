# Makefile for linux-c

CC = gcc
CFLAGS = -g -Wall -o

OBJS = tgetopt_long.o \
       mychmod.o

all : $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) $@ $<

clean:
	rm -rf *.o*
