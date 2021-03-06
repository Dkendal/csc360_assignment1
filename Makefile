CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-lreadline -llist
SOURCES=src/rsi.c src/prompt.c src/task.c src/path.c
TEST_SOURCES=test/prompt_test.c
OBJECTS=$(SOURCES:.c=.o)
TEST_OBJECTS=$(TEST_SOURCES:.c=.o)
EXECUTABLE=rsi
TEST_EXECUTABLE=test_runner

all: $(SOURCES) $(EXECUTABLE)

list:
	$(MAKE) -C list

$(EXECUTABLE): list $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -L./list/build $(LDFLAGS)

test: $(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS) -o $(TEST_EXECUTABLE) $(LDFLAGS)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) $(TEST_EXECUTABLE) $(TEST_OBJECTS)
	$(MAKE) -C list clean

.PHONY: test list
