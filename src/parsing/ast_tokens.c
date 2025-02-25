/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:02:59 by marvin            #+#    #+#             */
/*   Updated: 2025/01/24 13:12:38 by marvin           ###   ########.fr       */
/*   Updated: 2025/01/24 13:12:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	create_heredoc_node(t_ast_node **root, t_ast_node **current)
{
	t_ast_node	*heredoc_node;

	heredoc_node = create_node(NODE_HEREDOC, "<<");
	heredoc_node->left = *root;
	*root = heredoc_node;
	*current = *root;
}

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
	command_node->infile = 0;
	command_node->outfile = 0;
	if (!*root)
		*root = command_node;
	else if (*current)
		(*current)->right = command_node;
	*current = command_node;
}

void	create_word_node(t_ast_node **root,
				t_ast_node **current, t_tokens *tokens)
{
	t_ast_node	*word_node;

	word_node = create_node(NODE_WORD, tokens->value);
	word_node->infile = 0;
	word_node->outfile = 0;
	if (!*root)
		*root = word_node;
	else if (*current)
		(*current)->right = word_node;
	*current = word_node;
}

void	create_envp_node(t_ast_node **root,
				t_ast_node **current, t_tokens *tokens)
{
	t_ast_node	*env_var_node;

	env_var_node = create_node(NODE_ENV_VAR, tokens->value);
	env_var_node->infile = 0;
	env_var_node->outfile = 0;
	if (!*root)
		*root = env_var_node;
	else if (*current)
		(*current)->right = env_var_node;
	*current = env_var_node;
}
