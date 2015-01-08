CC=gcc
CFLAGS=-c -Wall
LDFLAGS=-lreadline
SOURCES=src/main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)
