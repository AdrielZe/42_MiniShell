NAME = minishell

CC = cc
CFLAGS = -g3 # -Wall -Wextra -Werror (coloque se precisar)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR) -Isrc/tokenize
SRC_DIR = src
OBJ_DIR = obj
BUILT_INS = built-ins
LIBS = -lreadline

# Pega todos os .c dentro de src/
SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Pega todos os .c dentro de built-ins/
SRC_BUILTINS = $(shell find $(BUILT_INS) -name "*.c")
OBJS_BUILTINS = $(patsubst $(BUILT_INS)/%.c, built-ins/%, $(SRC_BUILTINS))

all: $(LIBFT) $(NAME) built

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) $(INCLUDES) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)
	rm $(OBJS_BUILTINS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	rm $(OBJS_BUILTINS)

re: fclean all

built:
	$(CC) $(SRC_BUILTINS) -o $(OBJS_BUILTINS)

.PHONY: all clean fclean re
