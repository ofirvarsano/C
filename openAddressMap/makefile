# makefile Hash

CC=gcc
TARGET=$(shell basename $(CURDIR))_test.out
CFLAGS=-ansi -pedantic -Wall -g3 -Wconversion -Werror -c

OBJS=openAddressMap.o openAddressMap_test.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

run: $(TARGET)
	./$(TARGET)
	
gdb: $(TARGET)
	gdb ./$(TARGET)
	
valgrind: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

clean:
	rm -f *.out *.o

openAddressMap.o: openAddressMap.c HashMap.h
openAddressMap_test.o: openAddressMap_test.c HashMap.h
