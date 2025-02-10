/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/01/24 13:06:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

static void	left_process(int *pipe, t_ast_node *node, char **envp)
{
	if (dup2(pipe[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 left");
		exit(1);
	}
	close(pipe[0]);
	close(pipe[1]);
	parse_commands(node->left, envp);
	exit(0);
}

static void	right_process(int *pipe, t_ast_node *node, char **envp)
{
	if (dup2(pipe[0], STDIN_FILENO) == -1)
	{
		perror("dup2 right");
		exit(1);
	}
	close(pipe[0]);
	close(pipe[1]);
	parse_commands(node->right, envp);
	exit(0);
}

static void	open_left_pipe(int *pipefd, pid_t *pid_left) //Tudo o que esse processo imprimir será enviado pelo pipe para o próximo comando.
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	*pid_left = fork();
	if (*pid_left < 0)
	{
		perror("fork left");
		return ;
	}
}

static void	open_right_pipe(pid_t *pid_right)
{
	*pid_right = fork();
	if (*pid_right < 0)
	{
		perror("fork right");
		return ;
	}
}

void	parse_commands(t_ast_node *node, char **envp)
{
	pid_t	pid_left;
	pid_t	pid_right;	
	pid_t	pid;
	int		pipefd[2];

	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		open_left_pipe(pipefd, &pid_left);
		if (pid_left == 0)
			left_process(pipefd, node, envp);
		open_right_pipe(&pid_right);
		if (pid_right == 0)
			right_process(pipefd, node, envp);
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid_left, NULL, 0);
		waitpid(pid_right, NULL, 0);
	}
	else if (node->type == NODE_HEREDOC)
	{	
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			return ;
		}

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}

		if (pid == 0)
		{
			close(pipefd[0]);
			char	*input;
			char	*delimiter;

			delimiter = ft_split(node->right->value, ' ')[0];

			while (1)
			{
				input = readline("heredoc> ");
				if (!input || ft_strcmp(input, delimiter) == 0)
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
		waitpid(pid, NULL, 0);
		close(pipefd[1]);
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}

		if (pid == 0)
		{
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			
			char *cmd_path = search_valid_path(node->left->value, envp);
			char *args[] = {node->left->value, NULL};
			execute_command(node->left->value, envp);
			exit(1);
		}
		close (pipefd[0]);
		waitpid(pid, NULL, 0);
	}
	else if (node->type == NODE_COMMAND)
		execute_command(node->value, envp);
}
