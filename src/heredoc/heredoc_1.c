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

void	process_heredoc_input(int *pipefd,
			char **input, t_ast_node *node, char **envp)
{
	display_input_line(input, envp, node);
	if (!(*input))
	{
		close_pipefd(pipefd);
		exit(1);
	}
	remove_quotes(*input);
	*input = process_env_var(*input, 1);
	if (!(*input))
	{
		close_pipefd(pipefd);
		exit(1);
	}
}

void	handle_heredoc_delimiters(int *pipefd,
			t_delim *delimiters, t_ast_node *node, char **envp)
{
	t_delim	*current;
	char	*input;

	current = delimiters;
	while (current)
	{
		while (1)
		{
			process_heredoc_input(pipefd, &input, node, envp);
			if (ft_strcmp(input, current->delimiter) == 0)
			{
				free(input);
				current = current->next;
				break ;
			}
			write_and_free_input(pipefd, input);
		}
	}
}

void	read_heredoc(int *pipefd,
	t_delim *delimiters, t_ast_node *node, char **envp)
{
	int	newfd[2];
	int	save_dup;
	int	save_out;

	save_out = dup(STDOUT_FILENO);
	save_dup = dup(STDIN_FILENO);
	if (pipe(newfd))
	{
		perror("pipe failed");
		return ;
	}
	handle_heredoc_delimiters(newfd, delimiters, node, envp);
	dup2(newfd[0], STDIN_FILENO);
	if (node->right->outfile)
		dup2(node->right->outfile, STDOUT_FILENO);
	else
		dup2(pipefd[1], STDOUT_FILENO);
	close(newfd[1]);
	handle_command_node(node->left, envp);
	close(pipefd[1]);
	dup2(save_dup, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close_pipefd(newfd);
	close_pipefd(pipefd);
	exit(0);
}

void	execute_command_with_heredoc(int *pipefd, pid_t pid,
			t_ast_node *node, char **envp)
{
	t_ast_node	*current;
	int			pipe_found;
	int			status;

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
			close_pipefd(pipefd);
			exit(1);
		}
		read_heredoc(pipefd, delim_list, node, envp);
		exit(0);
	}
	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
		execute_command_with_heredoc(pipefd, pid, node, envp);
	close(pipefd[0]);
	set_signal_handler(handle_sigint);
}
