/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/28 17:44:00 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <signal.h>

void	handle_command_not_found(char **cmd, char *cmd_path)
{
	if (cmd_path == NULL)
	{
		printf("minishell: %s: command not found\n", cmd[0]);
		write_exitcode(127);
		free_array(cmd);
	}
	free(cmd_path);
}

void	check_and_execute_if_is_cmd(t_ast_node *node, char **envp)
{
	char	**cmd;
	char	*cmd_path;

	cmd = ft_split(node->value, ' ');
	if (!cmd)
		return ;
	cmd_path = search_valid_path(cmd[0], envp);
	if (!cmd_path || cmd[0] == NULL)
	{
		free_array(cmd);
		return ;
	}
	handle_command_not_found(cmd, cmd_path);
	if (is_directory(node->value) == 0)
	{
		printf("minishell: %s: Is a directory\n", node->value);
		write_exitcode(126);
		free_array(cmd);
		return ;
	}
	execute_command(node->value, envp, node);
	free_array(cmd);
}

void	handle_command_with_slash(t_ast_node *node,
		char **split_values, char *command_to_execute, char **envp)
{
	char	*search_result;
	char	**split_path;

	search_result = search_valid_path(command_to_execute, envp);
	if (control_command_execution_with_slash(&split_path, node, envp) == 1)
	{
		free_array(split_values);
		free(search_result);
		return ;
	}
	else if (not_result_msg_free(search_result,
			node, split_values, command_to_execute) == 1)
	{
		free_array(split_path);
		free(search_result);
		return ;
	}
	execute_simple_quote_node(node, node->value, envp);
	free(search_result);
	free_array(split_values);
}

void	execute_regular_cmd(t_ast_node *node, char **envp)
{
	char	*command_to_execute;
	char	**split_values;

	rmv_quotes_set_cmd(node, &split_values, &command_to_execute);
	if (!node->value || node->value[0] == '\0')
		return ;
	if (ft_strchr(node->value, '/') != NULL)
	{
		handle_command_with_slash(node, split_values, command_to_execute, envp);
		return ;
	}
	execute_simple_quote_node(node, node->value, envp);
	free_array(split_values);
}

int	verify_if_is_env_var(t_ast_node *node)
{
	char	*old_string;

	if (!node->value || node->value[0] == '\0')
		return (0);
	old_string = ft_strdup(node->value);
	node->value = process_env_var(node->value, 0);
	if (ft_strcmp(old_string, node->value) != 0)
	{
		free(old_string);
		return (1);
	}
	free(old_string);
	return (0);
}
