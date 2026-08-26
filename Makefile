CC = gcc
AR = ar
ARFLAGS = rcs
CFLAGS = -Wall -Wextra -Iinclude/ -MMD -MP
LDFLAGS = -lm -g 
SRCDIR = src
OBJDIR = obj
BINDIR = bin
LIBDIR = lib
TESTDIR = tests
TESTOUTPUTDIR = $(TESTDIR)/output/bin
LIBNAME = bigra9m
STATIC_LIB = $(LIBDIR)/lib$(LIBNAME).a

# Find all .c files recursively, excluding main.c for library objects
LIB_SOURCES = $(shell find $(SRCDIR) -type f -name '*.c' ! -name 'main.c')
MAIN_SOURCE = $(SRCDIR)/main.c
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(LIB_SOURCES))
MAIN_OBJECT = $(OBJDIR)/main.o

# Find all test sources and generate test binary names
TEST_SOURCES = $(wildcard $(TESTDIR)/test_*.c)
TEST_BINS = $(patsubst $(TESTDIR)/test_%.c,$(TESTOUTPUTDIR)/run_tests_%,$(TEST_SOURCES))

# Dependency files
DEPS = $(OBJECTS:.o=.d) $(MAIN_OBJECT:.o=.d)

# Prevent test binaries from being deleted
.SECONDARY: $(TEST_BINS)

# Default target - builds static library and main binary
all: $(STATIC_LIB) $(BINDIR)/main

# Create static library from all objects (except main.o)
$(STATIC_LIB): $(OBJECTS)
	@mkdir -p $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $^
	@echo "Created $@"

# Main target - links against static library
$(BINDIR)/main: $(MAIN_OBJECT) $(STATIC_LIB)
	@mkdir -p $(BINDIR)
	$(CC) $(MAIN_OBJECT) -L$(LIBDIR) -l$(LIBNAME) $(LDFLAGS) -o $@
	@echo "Created $@"

# Alias for convenience
main: $(BINDIR)/main

# Compile rule for main.c
$(OBJDIR)/main.o: $(MAIN_SOURCE)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile rule for library sources
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Main test suite - links against static library
test: $(TEST_BINS)
	@for test_bin in $(TEST_BINS); do \
		echo "\n=== Running $$test_bin ==="; \
		./$$test_bin || exit 1; \
	done

# Pattern rule for test binaries - link against static library
$(TESTOUTPUTDIR)/run_tests_%: $(TESTDIR)/test_%.c $(STATIC_LIB)
	@mkdir -p $(TESTOUTPUTDIR)
	$(CC) $(CFLAGS) $< -L$(LIBDIR) -l$(LIBNAME) $(LDFLAGS) -o $@

# Run specific test
test-%: $(TESTOUTPUTDIR)/run_tests_%
	./$(TESTOUTPUTDIR)/run_tests_$*

.PHONY: all clean test main lib

# Build only the library
lib: $(STATIC_LIB)

# Clean targets
clean:
	rm -rf $(OBJDIR) $(BINDIR) $(LIBDIR) $(TESTOUTPUTDIR)

clean-main:
	rm -rf $(OBJDIR) $(BINDIR)

clean-lib:
	rm -rf $(OBJDIR) $(LIBDIR)

clean-tests:
	rm -rf $(TESTOUTPUTDIR)

# Include dependency files
-include $(DEPS)