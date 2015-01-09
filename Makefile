CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-lreadline
SOURCES=src/rsi.c src/prompt.c src/argv.c
TEST_SOURCES=test/prompt_test.c
OBJECTS=$(SOURCES:.c=.o)
TEST_OBJECTS=$(TEST_SOURCES:.c=.o)
EXECUTABLE=rsi
TEST_EXECUTABLE=test_runner

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

test: $(TEST_OBJECTS)
	$(CC) $(TEST_OBJECTS) -o $(TEST_EXECUTABLE) $(LDFLAGS)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) $(TEST_EXECUTABLE) $(TEST_OBJECTS)
