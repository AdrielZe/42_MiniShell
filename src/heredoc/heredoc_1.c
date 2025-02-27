/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:41:35 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/26 22:06:29 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

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

void	read_heredoc(int *pipefd, t_delim *delimiters)
{
	char	*input;
	t_delim	*current;

	current = delimiters;
	while (current)
	{
		while (1)
		{
			input = readline("heredoc> ");
			if (!input)
				break ;
			if (!ft_strcmp(input, current->delimiter))
			{
				free(input);
				current = current->next;
				break ;
			}
			write(pipefd[1], input, ft_strlen(input));
			write(pipefd[1], "\n", 1);
			free(input);
		}
	}
	close(pipefd[1]);
	free_delimiters(delimiters);
	exit(0);
}

void	execute_command_with_heredoc(int *pipefd,
			pid_t pid, t_ast_node *node, char **envp)
{
	t_ast_node	*current;
	int			pipe_found;

	current = node;
	pipe_found = 0;
	waitpid(pid, NULL, 0);
	close(pipefd[1]);
	pid = fork();
	protect_fork(pipefd);
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		handle_nodes_to_execute_command(current, pipe_found, node, envp);
		check_all_commands(node, envp);
		exit(1);
	}
	close(pipefd[0]);
	waitpid(pid, NULL, 0);
}

void	handle_heredoc(t_ast_node *node, char **envp)
{
	t_delim	*delim_list;
	pid_t	pid;
	int		pipefd[2];

	open_heredoc_pipe(pipefd, &pid);
	if (pid == 0)
	{
		delim_list = get_all_delimiters(node);
		read_heredoc(pipefd, delim_list);
	}
	execute_command_with_heredoc(pipefd, pid, node, envp);
}
