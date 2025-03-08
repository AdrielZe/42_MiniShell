/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_regular_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:42:52 by marvin            #+#    #+#             */
/*   Updated: 2025/03/08 19:42:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <sys/stat.h>

void	rmv_quotes_set_cmd(t_ast_node *node, char ***split_values, char **command_to_execute)
{
	remove_quotes(node->value);
	if (node->type == NODE_COMMAND)
		get_cmd_to_execute(node, split_values, command_to_execute);
	else	
		*command_to_execute = ft_strdup(node->value);
}

int	control_command_execution_with_slash(char ***split_path, t_ast_node *node, char **envp)
{
	struct stat	path_stat;

	*split_path = ft_split(node->value, ' ');
	if (!*split_path)
		return (1);
	if (search_valid_path(*split_path[0], envp))
	{
		execute_command(node->value, envp, node);
		return (1);
	}
	if (node->type != NODE_COMMAND)
	{
		free(*split_path[0]);
		*split_path[0] = ft_strdup(node->value);
	}
	if (stat(node->value, &path_stat) != 0)
		printf("minishell: %s: No such file or directory\n", *split_path[0]);
	else if (S_ISDIR(path_stat.st_mode))
		printf("minishell: %s: Is a directory\n", *split_path[0]);
	else if (access(node->value, X_OK) != 0)
		printf("minishell: %s: Permission denied\n", *split_path[0]);
	else
		execute_command(node->value, envp, node);
	return (0);
}