NAME = minishell

CC = cc
CFLAGS = -g3 # -Wall -Wextra -Werror (adicione se precisar)

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)
SRC_DIR = src
OBJ_DIR = obj
BUILT_INS = built-ins
LIBS = -lreadline

# Pega todos os .c dentro de src/
SRCS = $(shell find $(SRC_DIR) -name "*.c")
SRCS += $(BUILT_INS)/cd.c #Adiciona um arquivo avulço a srcs
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Pega todos os .c dentro de built-ins/
SRC_BUILTINS = $(shell find $(BUILT_INS) -name "*.c" ! -name "cd.c")
BUILT_EXECUTABLES = $(patsubst $(BUILT_INS)/%.c, $(BUILT_INS)/%, $(SRC_BUILTINS))

all: $(LIBFT) $(NAME) built

# Regra para compilar minishell
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) $(INCLUDES) -o $(NAME)

# Compilação dos objetos do minishell
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Regra para compilar a libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -f $(BUILT_EXECUTABLES)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

# Compilação de cada built-in separadamente
built: $(BUILT_EXECUTABLES)

$(BUILT_INS)/%: $(BUILT_INS)/%.c $(LIBFT)
	$(CC) $< $(INCLUDES) $(LIBFT) -o $@

.PHONY: all clean fclean re built
