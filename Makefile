SRC_DIRS := . lexer parser eval utils
TARGET := HolyCpp

CC := cc
STD := c17
FLAGS := -std=$(STD) -Wall -Wextra -Wpedantic

SRC := $(foreach d, $(SRC_DIRS), $(wildcard $(d)/*.c))
OBJS := $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o $@

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean: 
	$(RM) $(OBJS) $(TARGET)


