CC = gcc
CFLAGS = -Wall -Wextra -Iinclude 
LDFLAGS =  
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

# Clean update
clean:
	rm -rf $(OBJDIR) main 

