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
int	cd(char *argv[]);
void	add_exitcode(int status);
void	set_signal_handler(void (*handler)(int));
int		ft_exit(char *args, char **envp, struct s_tokens **token_list, struct s_ast_node *node);
void sigint_cat_action(int sig);
int* get_heredoc_status(void);
void	sigint_heredoc_action(int sig);
//src/main.c
int		array_len(char **array);
char	**copy_envp(char *envp[]);

//src/init_minishell.c
void	init_shell(char ***token, struct s_tokens **token_list,
			char **envp, struct s_ast_node **root);

//src/init_utils.c
void	free_ast(struct s_ast_node *node);
void	exit_if_typed_exit(char *input,
			struct s_tokens **token_list, char **envp_copy);
void	setup_tokens_and_build_ast(char *input,
			struct s_tokens **token_list, char **envp, char ***token);
void	manage_rl_input(char **input,
			char **envp, struct s_tokens **token_list, struct s_ast_node *root);

//src/signals/sig_int.c
void	handle_sigint(int sig);
void	handle_ctrl_d(char **envp_copy, struct s_tokens **token_list,
			struct s_ast_node *root);
void	sigquit_handler(int sig);

//src/env_var/process_env_var.c
char	*process_env_var(char *input, int is_heredoc);
void	open_exitcode(void);
void	write_exitcode(int exitcode);

#endif