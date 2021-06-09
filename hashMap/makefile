# makefile Hash

CC=gcc
TARGET=$(shell basename $(CURDIR))_test.out
CFLAGS=-ansi -pedantic -Wall -g3 -Wconversion -Werror -c
CFLAGS+= -fPIC
OBJS=hashMap.o hashMap_test.o

LIB_OBJS=hashMap.o
LIB_DIR=../lib
LDFLAGS=-L$(LIB_DIR) -lDS
LDFLAGS+=-Wl,-rpath=$(CURDIR)/../lib/

SRCS=$(OBJS:.o=.c)

lib: $(LIB_OBJS)

$(TARGET): hashMap_test.o
	$(CC) -o $(TARGET) hashMap_test.o $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)
	
gdb: $(TARGET)
	gdb ./$(TARGET)

#hashMap.o: hashMap.c HashMap.h
#	$(CC) $(CFLAGS) hashMap.c
#
#hashMap_test.o: hashMap_test.c HashMap.h
#	$(CC) $(CFLAGS) hashMap_test.c
	
valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) *.o depends
	
depends: 
	$(CC) -MM -I./ $(SRCS) > depends
		
include depends

