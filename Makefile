CC = gcc
CFLAGS = -Wall -Wextra -Iinclude/
LDFLAGS = -lm -g -lgmp
SRCDIR = src
OBJDIR = obj

# Find all .c files recursively
SOURCES = $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

# Main target
main: $(OBJECTS)
	$(CC) $^ $(LDFLAGS) -o $@

# Compile rule
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


# Test - includes all source files recursively
test:
	$(CC) $(CFLAGS) tests/test_main.c src/*.c src/brz/*.c $(LDFLAGS) -o run_tests && ./run_tests

# Run specific test
test-%:
	$(CC) $(CFLAGS) tests/test_$*.c $(shell find src/ -type f -name '*.c' ! -name 'main.c') $(LDFLAGS) -o ./tests/output/bin/run_tests_$* && ./tests/output/bin/run_tests_$*

.PHONY: clean test


# Clean update
clean:
	rm -rf $(OBJDIR) main tests/output/bin/*

