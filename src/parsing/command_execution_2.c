/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/28 15:20:13 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <sys/stat.h>

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		return (1);
	return (0);
}

int	is_file(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISREG(path_stat.st_mode));
}

void	handle_node_types(t_ast_node *node, char **envp, t_delim **delimiters)
{
	int	is_env_var;

	is_env_var = 0;
	if (node->type == NODE_HEREDOC)
	{
		*delimiters = get_all_delimiters(node);
		handle_heredoc(node, envp);
		free_delimiters(*delimiters);
	}
	else if (node->type == NODE_WORD)
		handle_word_node(node, envp);
	else if (node->type == NODE_COMMAND)
		handle_command_node(node, envp);
	else if (node->type == NODE_SIMPLE_QUOTE)
	{
		printf("Chamou\n");
		handle_simple_quote_node(node, envp);
	}
}
