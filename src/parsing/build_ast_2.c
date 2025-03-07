/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:48:43 by marvin            #+#    #+#             */
/*   Updated: 2025/03/06 21:48:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	create_nodes_and_redirect_if(t_tokens **tokens,
		t_ast_node **root, t_ast_node **current)
{
	if (!tokens || !*tokens)
		return ;
	if ((*tokens)->type == TOKEN_PIPE)
		create_pipe_node(root, current);
	else if ((*tokens)->type == TOKEN_HEREDOC)
		create_heredoc_node(root, current);
	else if ((*tokens)->type == TOKEN_COMMAND || (*tokens)->type == TOKEN_WORD)
		handle_cmd_or_word_token(*tokens, root, current);
	else if ((*tokens)->type == TOKEN_ENV_VAR)
		create_envp_node(root, current, *tokens);
	else if ((*tokens)->type == TOKEN_SIMPLE_QUOTE)
		create_simple_quote_node(root, current, *tokens);
	else if (redirection_if(*tokens, *current))
	{
		if (*current && (*current)->infile == -1)
			return ;
		*tokens = (*tokens)->next;
	}
}
