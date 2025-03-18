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

void	rmv_quotes_set_cmd(t_ast_node *node,
				char ***split_values, char **command_to_execute)
{
	get_cmd_to_execute(node, split_values, command_to_execute);
}

int	control_stat(char *cmd_value,
		char ***split_path, t_ast_node *node, char **envp)
{
	struct stat	path_stat;

	if (stat(cmd_value, &path_stat) != 0)
	{
		printf("minishell: %s: No such file or directory\n", *split_path[0]);
		return (1);
	}
	else if (S_ISDIR(path_stat.st_mode))
	{
		printf("minishell: %s: Is a directory\n", *split_path[0]);
		return (1);
	}
	else if (access(node->value, X_OK) != 0)
	{
		printf("minishell: %s: Permission denied\n", *split_path[0]);
		return (1);
	}
	else
		execute_command(node->value, envp, node);
	return (0);
}

int	control_command_execution_with_slash(char ***split_path,
	t_ast_node *node, char **envp)
{
	char		*cmd_value;
	char		*split_value;
	char		*path;

	cmd_value = ft_strdup(node->value);
	*split_path = split_with_quotes(cmd_value);
	remove_quotes(cmd_value);
	if (!*split_path)
		return (1);
	path = search_valid_path(*split_path[0], envp);
	if (path != NULL)
	{
		execute_command(cmd_value, envp, node);
		free(cmd_value);
		free_array(*split_path);
		free(path);
		return (1);
	}
	free(path);
	if ((*split_path)[0][0] == '/')
	{
		node->value = *split_path[0];
		check_if_is_cmd_or_dir(node, envp);
		free(cmd_value);
		return (1);
	}
	if (node->type != NODE_COMMAND)
	{
		free(*split_path[0]);
		*split_path[0] = ft_strdup(cmd_value);
	}
	if (control_stat(cmd_value, split_path, node, envp) == 1)
	{
		free_array(*split_path);
		return (1);
	}
	free_array(*split_path);
	return (0);
}

int	not_result_msg_free(char *search_result,
			t_ast_node *node, char **split_values, char *command_to_execute)
{
	if (!search_result)
	{
		not_found_msg_and_free(node, search_result,
			split_values, command_to_execute);
		return (1);
	}
	return (0);
}
