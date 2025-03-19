/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:49:18 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/28 18:01:59 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

void	set_signal_handler(void (*handler)(int))
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

void	cleanup_heredoc_c(t_ast_node *node, char **envp)
{
	if (envp)
		free_array(envp);
	if (node)
	{
		free_ast(node);
		node = NULL;
	}
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	cleanup_heredoc(t_ast_node *node, char **envp)
{
	if (envp)
		free_array(envp);
	if (node)
	{
		free_ast(node);
		node = NULL;
	}
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	write(1, "\n> ", 3);
}

void	handle_ctrl_d(char **envp_copy, t_tokens **token_list, t_ast_node *root)
{
	write(1, "Exiting minishell\n", 19);
	cleanup_heredoc(root, envp_copy);
	clear_token_list(token_list);
	token_list = NULL;
	rl_clear_history();
	clear_history();
	exit(0);
}
