# Defining the compiler
CC = gcc

# Defining the compiler flags
CFLAGS = -Wall -Wextra

# Defining the target executable
TARGET = cpu

# Defining the source files
SRCS = src/cpu.c src/screen.c src/main.c

# Defining the object files
OBJS = $(SRCS:.c=.o)

# Rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lSDL2

# Rule to build object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean all generated files from the directory
clean:
	rm -f $(OBJS) $(TARGET)
