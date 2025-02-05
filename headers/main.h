/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:28:59 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/23 16:30:50 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <readline/readline.h> //readline
# include <readline/history.h> //readline history
# include <sys/wait.h> // waitpid
# include "../libft/libft.h" //libft
# include "tokenize.h"
# include "parsing.h"

struct	s_tokens;
struct	s_ast_node;

char	*process_env_var(char *input);
char	**tokenize(char const *s, char c);
void	init_shell(char ***token, struct s_tokens **token_list,
			char *envp[], struct s_ast_node **root);
void	print_ast(struct s_ast_node *node, int level);

#endif