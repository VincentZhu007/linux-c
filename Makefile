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
       ioctl_net.o \
       getinfo.o \
       t_umask.o \
       t_unlink.o \
       mycd.o \
       show_files.o \
       myls.o \
       t_fork.o \
       t_fork2.o \
       t_fork3.o

all : $(OBJS)

%.o : %.c
	$(CC) $(CFLAGS) $@ $<

clean:
	rm -rf *.o* *.txt
