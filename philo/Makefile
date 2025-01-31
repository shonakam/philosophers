NAME = philo

CFLAGS := -Wall -Werror -Wextra -pthread
INCLUDE := -I/includes

SRC_PATH := ./srcs/
SRCS := $(shell find $(SRC_PATH) -type f -name '*.c')
OBJS := $(patsubst $(SRC_PATH)%.c, objs/%.o, $(SRCS))

# CFLAGS += -fsanitize=address -g -fno-omit-frame-pointer
CFLAGS += -fsanitize=thread -g

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

objs/%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -rf objs/

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run

# .SILENT:
run: re
	./$(NAME)
