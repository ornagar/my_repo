#Makefile for watchdog
#Thanks to Atalia
CC = /usr/bin/gcc
LN = /bin/ln -fs
CDEBUG_FLAGS = -g -D_DEBUG -D_DLOG_FLOW
CRELEASE_FLAGS = -DNDEBUG
INC_DIR = .
LIB_NAME = libsch.so
CFLAGS = -Wall  -I$(INC_DIR)  -pedantic -fPIC $(CDEBUG_FLAGS)
LDFLAGS = -pthread

SCHED = scheduler.o scheduler_task.o uid.o pqueue.o \
		heapify.o heap.o d_vector.o

all: wd_test

wd_exec: wd_exec.o libsch.so
	$(CC) $(CFLAGS) wd_exec.c -o wd_exec $(LDFLAGS) \
		-Wl,-rpath=. $(LIB_NAME)

$(LIB_NAME): $(SCHED)
	$(CC) $(CFLAGS) -shared -o $(@) $(SCHED)
	$(LN) $(@).1.0 $(@).1
	$(LN) $(@).1 $(@)

wd_test: wd_test.o wd.o libsch.so wd_exec.o wd_exec
	$(CC) $(CFLAGS) wd_test.c wd.o \
		-o wd_test $(LDFLAGS) -Wl,-rpath=. $(INC_DIR)/$(LIB_NAME) 

-include .depends
depends:
	gcc -MM *.c > .depends

clean:
	rm *.o
