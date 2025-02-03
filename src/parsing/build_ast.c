/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:32:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/29 16:00:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->value)
		free(node->value);
	free(node);
}

t_ast_node	*create_node(t_node_type type, char *value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(value);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*build_ast(t_tokens *tokens)
{
	t_ast_node	*root;
	t_ast_node	*current;

	current = NULL;
	root = NULL;
	while (tokens)
	{
		if (tokens->type == TOKEN_PIPE)
			create_pipe_node(&root, &current);
		else if (tokens->type == TOKEN_COMMAND)
			create_command_node(&root, &current, tokens);
		tokens = tokens->next;
	}
	return (root);
}

void	parse_commands(t_ast_node *node, char **envp)
{
	int	pipefd[2];
	pid_t	pid_left = fork();

	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			return ;
		}
		if (pid_left < 0)
		{
       		perror("fork left");
       		return ;
		}
		if (pid_left == 0) 
		{
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			{
				perror("dup2 left");
				exit(1);
			}
			close(pipefd[0]);
			close(pipefd[1]);
			parse_commands(node->left, envp);
			exit(0);		
		}
		pid_t pid_right = fork();
		if (pid_right < 0)
		{
			perror("fork right");
			return ;
		}		
		if (pid_right == 0)
		{
			if (dup2(pipefd[0], STDIN_FILENO) == -1)
			{
				perror("dup2 right");
				exit(1);
			}
			close(pipefd[0]);
			close(pipefd[1]);
			parse_commands(node->right, envp);
			exit(0);
		}
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(pid_left, NULL, 0);
		waitpid(pid_right, NULL, 0);
	}
	else if (node->type == NODE_COMMAND)
	{
		execute_command(node->value, envp);
	}
}
