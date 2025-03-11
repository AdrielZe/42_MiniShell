/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/28 15:20:13 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <sys/stat.h>

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (0);
	return (1);
}

int	is_file(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISREG(path_stat.st_mode));
}

void	handle_pipe_node(t_ast_node *node, char **envp)
{
	pid_t		pid_left;
	pid_t		pid_right;
	int			pipefd[2];
	t_delim		*delimiters;
	int			status;

	delimiters = get_all_delimiters(node);
	open_left_pipe(pipefd, &pid_left);
	 set_signal_handler(SIG_IGN);
	if (pid_left == 0)
	{
		left_process(pipefd, node, delimiters, envp);
	 	set_signal_handler(handle_sigint);

	}
	waitpid(pid_left, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return ;
	open_right_pipe(&pid_right);
	if (pid_right == 0)
		right_process(pipefd, node, envp);
	close_pipefd(pipefd);
	waitpid(pid_left, &status, 0);
	waitpid(pid_right, NULL, 0);
	add_exitcode(WEXITSTATUS(status));
	free_delimiters(delimiters);
}

void	handle_node_types(t_ast_node *node, char **envp, t_delim **delimiters)
{
	if (node->type == NODE_PIPE)
		handle_pipe_node(node, envp);
	else if (node->type == NODE_HEREDOC)
	{
		*delimiters = get_all_delimiters(node);
		handle_heredoc(node, envp);
		free_delimiters(*delimiters);
	}
	else if (node->type == NODE_WORD)
		handle_word_node(node, envp);
	else if (node->type == NODE_COMMAND)
		handle_command_node(node, envp);
	else if (node->type == NODE_SIMPLE_QUOTE)
	{
		handle_simple_quote_node(node, envp);
	}
}
