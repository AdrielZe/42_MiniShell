# Nome do executável
NAME = program

# Compilador e flags
CC = gcc -g3
CFLAGS = #-Wall -Wextra -Werror

# Diretórios e arquivos
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)
SRCS = src/main.c src/process_env_var.c src/tokenize.c
OBJS = $(SRCS:.c=.o)
LIBS = -lreadline

# Regra padrão
all: $(LIBFT) $(NAME)

# Compilar o programa principal
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) $(INCLUDES) -o $(NAME)

# Compilar a libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Limpar arquivos objetos
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

# Limpar tudo (objetos e executáveis)
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

# Recompilar tudo
re: fclean all

# Phony para evitar conflitos com arquivos reais
.PHONY: all clean fclean re
