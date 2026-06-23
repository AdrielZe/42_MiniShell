/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/20 16:50:13 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	handle_node_types(t_ast_node *node, char **envp, t_delim **delimiters)
{
	if (node->type == NODE_HEREDOC)
	{
		*delimiters = get_all_delimiters(node);
		handle_heredoc(node, envp);
	}
	else if (node->type == NODE_COMMAND)
	{
		node->value = process_env_var(node->value);
		execute_command(node->value, envp, node);
	}
}
