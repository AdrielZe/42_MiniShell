/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:41:35 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/10 20:38:25 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	protect_fork(pid_t *pid)
{
	if (*pid < 0)
	{
		perror("fork");
		return ;
	}
}

void	open_heredoc_pipe(int *pipefd, pid_t *pid)
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

void	read_heredoc(int *pipefd, char *delimiter)
{
	char	*input;

	close(pipefd[0]);
	while (1)
	{
		input = readline("heredoc> ");
		if (!input || !ft_strcmp(input, delimiter))
		{
			free(input);
			break ;
		}
		write(pipefd[1], input, ft_strlen(input));
		write(pipefd[1], "\n", 1);
		free(input);
	}
	close(pipefd[1]);
	exit(0);
}

void	execute_command_with_heredoc(int *pipefd,
			pid_t pid, t_ast_node *node, char **envp)
{
	char	**args;

	args = malloc(2 * sizeof(char *));
	args[0] = node->left->value;
	args[1] = NULL;
	search_valid_path(node->left->value, envp);
	waitpid(pid, NULL, 0);
	close(pipefd[1]);
	pid = fork();
	protect_fork(pipefd);
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_command(node->left->value, envp, node);
		exit(1);
	}
	close(pipefd[0]);
	waitpid(pid, NULL, 0);
}

void	handle_heredoc(t_ast_node *node, char **envp)
{
	pid_t	pid;
	int		pipefd[2];
	char	*delimiter;

	open_heredoc_pipe(pipefd, &pid);
	if (pid == 0)
	{
		delimiter = ft_split(node->right->value, ' ')[0];
		read_heredoc(pipefd, delimiter);
	}
	execute_command_with_heredoc(pipefd, pid, node, envp);
}
