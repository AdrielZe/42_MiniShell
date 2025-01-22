/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:02:59 by marvin            #+#    #+#             */
/*   Updated: 2025/01/22 16:02:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

void	create_pipe_node(t_ast_node	**root, t_ast_node **current)
{
	t_ast_node	*pipe_node;

	pipe_node = create_node(NODE_PIPE, "|");
	pipe_node->left = *root;
	*root = pipe_node;
	*current = *root;
}

void	create_command_node(t_ast_node **root,
				t_ast_node **current, t_tokens *tokens)
{
	t_ast_node	*command_node;

	command_node = create_node(NODE_COMMAND, tokens->value);
	if (!*root)
		*root = command_node;
	else if (*current)
		(*current)->right = command_node;
	*current = command_node;
}
