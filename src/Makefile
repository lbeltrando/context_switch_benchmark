CC = gcc

CPPFLAGS = -I.
CFLAGS = -Wall

LDFLAGS =
LIBS =

SRC = thread.c processus.c test_time.c context_thread.c context_proc.c
OBJ= $(SRC:.c=.o)

.PHONY: clean,mrproper

.SUFFIXES:

all: $(OBJ)
	$(CC) $(CPPFLAGS) $(CFLAGS) processus.c -o processus_test
	$(CC) $(CPPFLAGS) $(CFLAGS) thread.c -o thread_test -lpthread
	$(CC) $(CPPFLAGS) $(CFLAGS) test_time.c -o test_time
	$(CC) $(CPPFLAGS) $(CFLAGS) context_thread.c -o test_context_thread -lpthread
	$(CC) $(CPPFLAGS) $(CFLAGS) context_proc.c -o test_context_proc -lpthread

processus.o: processus.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c processus.c

thread.o: thread.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c thread.c

test_time.o: test_time.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c test_time.c

context_thread.o: context_thread.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c context_thread.c

context_proc.o: context_proc.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c context_proc.c

clean:
	rm -rf $(OBJ)

mrproper: clean
	rm -rf processus_test
	rm -rf thread_test
	rm -rf test_time
	rm -rf test_context_thread
	rm -rf test_context_proc
