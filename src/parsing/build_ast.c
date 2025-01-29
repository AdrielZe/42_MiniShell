/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:32:49 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/29 15:59:15 by marvin           ###   ########.fr       */
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
	if (node->type == NODE_COMMAND)
		execute_command(node->value, envp);
	}
	if (node->left)
	{
		left_result = parse_commands(node->left, envp);
		result = ft_realloc(result, ft_strlen(result) + ft_strlen(left_result) + 1);
		ft_strcat(result, left_result);
		free(left_result);
	}
	if (node->right)
	{
		right_result = parse_commands(node->right, envp);
		result = ft_realloc(result, ft_strlen(result) + ft_strlen(right_result) + 1);
		ft_strcat(result, right_result);
		free(right_result);
	}
	return (result);
}
