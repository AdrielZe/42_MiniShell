/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:41:35 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/26 23:02:43 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <signal.h>

static void	protect_fork(pid_t *pid)
{
	if (*pid < 0)
	{
		perror("fork");
		return ;
	}
}

static void	open_heredoc_pipe(int *pipefd, pid_t *pid)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	*pid = fork();
	if (*pid < 0)
	{
		perror("fork");
		return ;
	}
}

void	read_heredoc(int *pipefd, t_delim *delimiters, t_ast_node *node, char **envp)
{
	t_heredoc_data	*data;
	t_delim			*current;
	char			*input;

	data = get_heredoc_data();
	data->pipefd = pipefd;
	data->delimiters = delimiters;
	current = delimiters;
	while (current)
	{
		while (1)
		{
			display_input_line(&input, envp, node);
			if (!input)
			{
				close_pipefd(pipefd);
				free_delimiters(delimiters);
				exit(1);
			}
			remove_quotes(input);
			input = process_env_var(input, 1);
			if (!input)
			{
				close_pipefd(pipefd);
				free_delimiters(delimiters);
				exit(1);
			}
			if (ft_strcmp(input, current->delimiter) == 0)
			{
				free(input);
				current = current->next;
				break ;
			}
			write_and_free_input(pipefd, input);
		}
	}
	close_pipefd(pipefd);
	exit(0);
}

void	execute_command_with_heredoc(int *pipefd, pid_t pid,
			t_ast_node *node, char **envp)
{
	t_ast_node	*current;
	int			pipe_found;
	int			status;

	printf("aaaaaaaa\n");
	current = node;
	pipe_found = 0;
	pid = fork();
	protect_fork(&pid);
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		handle_nodes_to_execute_command(current, pipe_found, node, envp);
		check_all_commands(node, envp);
		close(pipefd[0]);
		exit(1);
	}
	close(pipefd[0]);
	waitpid(pid, &status, 0);
	write_exitcode(126);
}

void	handle_heredoc(t_ast_node *node, char **envp)
{
	t_delim	*delim_list;
	pid_t	pid;
	int		pipefd[2];
	int		status;

	open_heredoc_pipe(pipefd, &pid);
	set_signal_handler(SIG_IGN);
	if (pid == 0)
	{
		set_signal_handler(sigint_heredoc_action);
		delim_list = get_all_delimiters(node);
		if (!delim_list)
		{
			close(pipefd[0]);
			close(pipefd[1]);
			exit(1);
		}
		read_heredoc(pipefd, delim_list, node, envp);
		exit(0);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		execute_command_with_heredoc(pipefd, pid, node, envp);
	// if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	// {
	// 	free_array(envp);
	// }
	close(pipefd[0]);
	set_signal_handler(handle_sigint);
}
