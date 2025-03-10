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
	if (node->left)
		free_ast(node->left);
	if (node->right)
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
	node->outfile = -1;
	node->infile = -1;
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
	{
		//free(node->value);
		node->value = NULL;
	}
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	redirection_if(t_tokens *tokens, t_ast_node *node)
{
	if (!tokens->next && node->type != NODE_WORD)
	{
		ft_putstr_fd("Erro de sintaxe!\n", STDERR_FILENO);
		return (0);
	}
	if (tokens->type == TOKEN_REDIRECT_IN)
	{
		node->infile = open_stdin(tokens->next->value);
		node->outfile_type = NODE_REDIRECT_IN;
		return (1);
	}
	else if (tokens->type == TOKEN_REDIRECT_OUT)
	{
		node->outfile = open_stdout(tokens->next->value);
		return (1);
	}
	else if (tokens->type == TOKEN_APPEND)
	{
		node->outfile = open_append(tokens->next->value);
		node->outfile_type = NODE_APPEND;
		return (1);
	}
	return (0);
}

void	handle_cmd_or_word_token(t_tokens *tokens,
				t_ast_node **root, t_ast_node **current)
{
	char	*token_value;

	if (tokens->type == TOKEN_WORD)
		create_word_node(root, current, tokens);
	else
		create_command_node(root, current, tokens);
}

t_ast_node	*build_ast(t_tokens *tokens)
{
	t_ast_node	*root;
	t_ast_node	*current;

	root = NULL;
	current = NULL;
	while (tokens)
	{
		create_nodes_and_redirect_if(&tokens, &root, &current);
		if (tokens)
			tokens = tokens->next;
	}
	return (root);
}
