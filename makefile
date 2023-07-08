# Makefile

# Compiler
CC = clang++

# Compiler flags
CFLAGS = -std=c++11 -Wall -Wextra -Wno-missing-braces -g

# Linker flags
LDFLAGS = -lraylib 

# Target
TARGET = out
FILES = main.cpp trex.cpp
COMPS = main.o trex.o

all: $(TARGET)

$(TARGET): main.cpp
	$(CC) $(CFLAGS) -c $(FILES) $(LDFLAGS)
	$(CC) $(CFLAGS) -o $(TARGET) $(COMPS) $(LDFLAGS)

run:
	./$(TARGET)

clean:
	rm -f $(COMPS) $(TARGET)

