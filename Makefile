# Makefile for linux-c

CC = gcc
CFLAGS = -g -Wall -o

OBJS = tgetopt_long.o \
       mychmod.o \
       mycreate.o \
       myread.o \
       mywrl.o \
       fcntl_access.o \
       fcntl_lock.o \
       ioctl_net.o 

all : $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) $@ $<

clean:
	rm -rf *.o*
