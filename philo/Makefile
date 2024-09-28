NAME = philo

CFLAGS := #-Wall -Werror -Wextra
INCLUDE := -I/includes

SRC_PATH := ./srcs/
SRCS := $(shell find $(SRC_PATH) -type f -name '*.c')
OBJS := $(patsubst $(SRC_PATH)%.c, objs/%.o, $(SRCS))

# CFLAGS += -fsanitize=address -g -fno-omit-frame-pointer
# CFLAGS += -fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

objs/%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@rm -rf objs/

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re run

# .SILENT:
run: re
	./$(NAME)
