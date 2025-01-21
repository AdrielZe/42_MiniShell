/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:38:26 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/21 17:27:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "../headers/main.h"

typedef enum e_node_type
{
	NODE_WORD,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_APPEND,
	NODE_HEREDOC,
	NODE_ENV_VAR,
	NODE_COMMAND,
}	t_node_type;

typedef struct s_ast_node
{
	t_node_type	type;
	char		*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
} t_ast_node;

t_ast_node *create_node(t_node_type type, char *value);
t_ast_node	*build_ast(t_tokens *tokens);
char *concatenate_commands(t_ast_node *node);

#endif