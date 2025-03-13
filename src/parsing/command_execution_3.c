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

void	handle_word_node(t_ast_node *node, char **envp)
{
	char	*old_string;
	int		is_env_var;

	is_env_var = 0;
	if (!node->value || node->value[0] == '\0')
		return ;
	if (ft_strchr(node->value, '$') != NULL)
		is_env_var = 1;
	old_string = ft_strdup(node->value);
	node->value = process_env_var(node->value, 0);
	if (is_env_var == 1)
		when_only_env_var(node, envp);
	else if (ft_strcmp(old_string, node->value) != 0)
		check_and_execute_if_is_cmd(node, envp);
	else
		execute_regular_cmd(node, envp);
	free(old_string);
}

void	when_only_env_var(t_ast_node *node, char **envp)
{
	if (check_if_is_directory(node->value) == 0)
		return ;
	if (!is_file(node->value))
	{
		if (!search_valid_path(node->value, envp))
		{
			if (ft_strchr(node->value, '/'))
				printf("minishell: %s: No such file or directory\n",
					node->value);
			else
				printf("minishell: %s: command not found\n", node->value);
			return ;
		}
		return ;
	}
	execute_command(node->value, envp, node);
}

void	check_and_execute_if_is_cmd(t_ast_node *node, char **envp)
{
	char	**cmd;

	cmd = ft_split(node->value, ' ');
	if (!cmd)
		return ;
	if (cmd[0])
	{
		if (search_valid_path(cmd[0], envp) == NULL)
		{
			printf("minishell: %s: command not found\n",
				cmd[0]);
			add_exitcode(127);
			free_array(cmd, array_len(cmd));
			return ;
		}
	}
	if (is_directory(node->value) == 0)
	{
		printf("minishell: %s: Is a directory\n", node->value);
		free_array(cmd, array_len(cmd));
		return ;
	}
	else
		execute_command(node->value, envp, node);
	free_array(cmd, array_len(cmd));
}

void	execute_regular_cmd(t_ast_node *node, char **envp)
{
	char	*command_to_execute;
	char	**split_values;
	char	*search_result;
	char	**split_path;

	rmv_quotes_set_cmd(node, &split_values, &command_to_execute);
	search_result = search_valid_path(command_to_execute, envp);
	if (!node->value || node->value[0] == '\0')
		return ;
	if (ft_strchr(node->value, '/') != NULL)
	{
		if (control_command_execution_with_slash(&split_path,
				node, envp) == 1)
			return ;
		else if (not_result_msg_free(search_result,
				node, split_values, command_to_execute) == 1)
			return ;
		else
			execute_simple_quote_node(node, node->value, envp);
	}
	execute_simple_quote_node(node, node->value, envp);
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
