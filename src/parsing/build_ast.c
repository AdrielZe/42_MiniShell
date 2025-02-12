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
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	node->type = type;
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			perror("strdup failed");
			exit(EXIT_FAILURE);
		}
	}
	else
		node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static int	redirection_if(t_tokens *tokens, t_ast_node *node)
{
	if(!tokens->next)
	{
		ft_putstr_fd("Erro de sintaxe!\n", STDERR_FILENO);
		return (0);
	}
	if (tokens->type == TOKEN_REDIRECT_OUT)
	{
		node->outfile = tokens->next->value;
		node->outfile_type = NODE_REDIRECT_OUT;
		return (1);
	}
	else if (tokens->type == TOKEN_APPEND)
	{
		node->outfile = tokens->next->value;
		node->outfile_type = NODE_APPEND;
		return (1);
	}
	else if (tokens->type == TOKEN_REDIRECT_IN)
	{
		node->infile = open_stdin(tokens->next->value);
		node->outfile_type = NODE_REDIRECT_IN;
		return (1);
	}
	return (0);
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
		else if (tokens->type == TOKEN_HEREDOC)
			create_heredoc_node(&root, &current);
		else if (tokens->type == TOKEN_COMMAND)
			create_command_node(&root, &current, tokens);
		else if (redirection_if(tokens, current))
			tokens = tokens->next;
		tokens = tokens->next;
	}
	return (root);
}
