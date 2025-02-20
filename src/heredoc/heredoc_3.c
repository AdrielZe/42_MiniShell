/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:51:32 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/20 20:21:15 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	handle_nodes_to_execute_command(t_ast_node *current, int pipe_found,
		t_ast_node *node, char **envp)
{
	while (current->type != NODE_COMMAND)
	{
		current = current->left;
		if (current->type == NODE_PIPE && pipe_found == 0)
		{
			pipe_found = 1;
			if (node->right->outfile)
				dup2(node->right->outfile, STDOUT_FILENO);
			execute_command(current->right->value, envp, node);
		}
	}
	while (current)
	{
		if (current->type == NODE_COMMAND && pipe_found == 0
			/*&& node->infile == -1*/)
		{
			if (node->right->outfile)
				dup2(node->right->outfile, STDOUT_FILENO);
			execute_command(current->value, envp, node);
		}
		else
			search_valid_path(ft_split(current->value, ' ')[0], envp);
		current = current->left;
	}
	check_all_commands(node, envp);
	exit(1);
}
