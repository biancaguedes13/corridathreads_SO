CC = gcc
CFLAGS = -Wall -Wextra -pthread
TARGET = corrida
SRC = main.c threads.c
HEADERS = threads.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

	rm -f $(TARGET)

run: all
	./$(TARGET)
