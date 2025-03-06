/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tokens_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:38:10 by marvin            #+#    #+#             */
/*   Updated: 2025/03/06 16:38:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	create_simple_quote_node(t_ast_node **root,
	t_ast_node **current, t_tokens *tokens)
{
	t_ast_node	*simple_quote;

	simple_quote = create_node(NODE_SIMPLE_QUOTE, tokens->value);
	simple_quote->infile = 0;
	simple_quote->outfile = 0;
	if (!*root)
		*root = simple_quote;
	else if (*current)
		(*current)->right = simple_quote;
	*current = simple_quote;
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