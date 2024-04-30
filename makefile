# Define the compiler
CC=g++

# Define compiler options
CFLAGS=-std=c++20

# Define the target executable
TARGET=main

# List of source files
SOURCES=Main.cc Tokenizer.cc Parser.cc  # Add or remove files as necessary
OBJECTS=$(SOURCES:.cc=.o)

# Default target
all: $(TARGET)

# Build target executable from object files
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files
%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

# Run target
run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clean run
