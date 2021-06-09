# makefile generic executor

TARGET=$(shell basename $(CURDIR))_test.out
CC= gcc
CFLAGS= -pedantic -Wall -g3 -c
CFLAGS+= -fPIC
CFLAGS+=-I../genericHeap
OBJS=executor_test.o executor.o my_time.o task.o
LIB_OBJS=executor.o my_time.o task.o
LIB_DIR=../lib
LDFLAGS=-L$(LIB_DIR) -lDS
LDFLAGS+=-Wl,-rpath=$(CURDIR)/../lib

SRCS=$(OBJS:.o=.c)

lib: $(LIB_OBJS)

$(TARGET): executor_test.o
	$(CC) -o $(TARGET) executor_test.o $(LDFLAGS)
	
executor.o: executor.c executor.h my_time.h task.h
	$(CC) $(CFLAGS) executor.c
	
my_time.o: my_time.c my_time.h
	$(CC) $(CFLAGS) my_time.c	
	
task.o: task.c task.h
	$(CC) $(CFLAGS) task.c	
		
executor_test.o: executor_test.c executor.h my_time.h task.h
	$(CC) $(CFLAGS) executor_test.c	
	
run: $(TARGET)
	./$(TARGET)

valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) *.o depends
	
depends: 
	$(CC) -MM -I./ $(SRCS) > depends
		
include depends
