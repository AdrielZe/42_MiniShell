# Nome do executável
NAME = program

# Compilador e flags
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all
CC = cc
gdb = -g -O0 -fno-inline
CFLAGS = -Wall -Wextra -Werror

# Diretórios
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR) -Isrc/tokenize
SRC_DIR = src
OBJ_DIR = obj

# Procurar todos os arquivos .c no diretório src e subpastas
SRCS = $(shell find $(SRC_DIR) -name "*.c")
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
LIBS = -lreadline

all: $(LIBFT) $(NAME)

debug: GDB += -g
debug: re

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

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

valgrind: $(NAME) 
	$(VALGRIND) ./$(NAME)

.PHONY: all clean fclean re
