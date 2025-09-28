# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# The name of our final executable
TARGET = NanoZip

# List of all object files (.o) needed. Notice the lowercase names.
OBJS = main.o Huffman.o Heap.o

# The default rule: build the target executable
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET).exe $(OBJS)

# Rule to compile main.c into main.o
main.o: main.c Huffman.h
	$(CC) $(CFLAGS) -c main.c

# Rule to compile Huffman.c into Huffman.o
# IMPORTANT: The filenames here now match your actual files
Huffman.o: Huffman.c Huffman.h Heap.h
	$(CC) $(CFLAGS) -c Huffman.c

# Rule to compile Heap.c into Heap.o
# IMPORTANT: The filenames here now match your actual files
Heap.o: Heap.c Heap.h
	$(CC) $(CFLAGS) -c Heap.c

# Rule to clean up compiled files (Windows compatible)
clean:
	del /f /q $(TARGET).exe *.o