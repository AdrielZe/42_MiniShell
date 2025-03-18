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

void	cleanup_heredoc(void)
{
	t_heredoc_data	*data;

	data = get_heredoc_data();
	if (data->pipefd)
	{
		close(data->pipefd[0]);
		close(data->pipefd[1]);
		data->pipefd = NULL;
	}
	if (data->delimiters)
	{
		free_delimiters(data->delimiters);
		data->delimiters = NULL;
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
	free_array(envp_copy);
	if (root)
	{
		free_ast(root);
		root = NULL;
	}
	if (token_list)
	{
		clear_token_list(token_list);
		token_list = NULL;
	}
	envp_copy = NULL;
	rl_clear_history();
	clear_history();
	exit(0);
}

void	sigint_heredoc_action(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		cleanup_heredoc();
		exit(130);
	}
}
