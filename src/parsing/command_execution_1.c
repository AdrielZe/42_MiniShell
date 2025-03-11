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

void	left_process(int *pipe, t_ast_node *node,
		t_delim *delimiters, char **envp)
{
	t_ast_node	*current;

	current = node;
	while (current)
	{
		if (current->type == NODE_HEREDOC)
		{
			set_signal_handler(sigint_heredoc_action); 

			delimiters = get_all_delimiters(current);
			read_heredoc(pipe, delimiters);
			return ;
		}
		current = current->left;
	}
	if (verify_if_is_env_var(node->left) != 1)
	{
		if (dup2(pipe[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 left");
			exit(1);
		}
	}
	close(pipe[0]);
	close(pipe[1]);
	parse_commands(node->left, envp);
	exit(0);
}

void	right_process(int *pipe, t_ast_node *node, char **envp)
{
	if (!node || !node->right)
		return ;
	if (dup2(pipe[0], STDIN_FILENO) == -1)
	{
		perror("dup2 right");
		exit(1);
	}
	if (node->outfile)
	{
		dup2(node->outfile, STDOUT_FILENO);
	}
	close(pipe[0]);
	close(pipe[1]);
	parse_commands(node->right, envp);
	exit(0);
}

void	open_left_pipe(int *pipefd, pid_t *pid_left)
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

void	open_right_pipe(pid_t *pid_right)
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
	pid_t		pid_left;
	pid_t		pid_right;
	int			pipefd[2];
	t_delim		*delimiters;
	int			status;

	if (!node)
		return ;
	delimiters = NULL;
	handle_node_types(node, envp, &delimiters);
}
