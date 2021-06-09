# makefile sorts

TARGET= sorts.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= sorts.o vector.o stack.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
sorts.o: sorts.c
	$(CC) $(CFLAGS) -c sorts.c
	
vector.o: vector.c vector.h
	$(CC) $(CFLAGS) -c vector.c
	
stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c
	
run: $(TARGET)
	./$(TARGET)
clean:
	rm -f $(TARGET) $(OBJS)
