/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:32:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/24 13:54:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

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

char	*parse_commands(t_ast_node *node, char **envp)
{
	char	*result;

	if (!node)
		return (NULL);
	result = malloc(1);
	result[0] = '\0';
	if (node->type == NODE_COMMAND)
		execute_command(node->value, envp);
	if (node->left)
		result = parse_commands(node->left, envp);
	if (node->right)
		result = parse_commands(node->right, envp);
	return (result);
}
