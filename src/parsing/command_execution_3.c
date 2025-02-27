/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/26 21:59:07 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <sys/stat.h>

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
	node->value = process_env_var(node->value);
	if (is_env_var == 1)
	{
		when_only_env_var(node, envp, old_string);
	}
	else if (ft_strcmp(old_string, node->value) != 0)
		check_and_execute_if_is_cmd(node, envp);
	else
	{	
		printf("checking\n");
		execute_regular_cmd(node, envp);
		free(old_string);
	}
}

void	when_only_env_var(t_ast_node *node, char **envp, char *old_string)
{
	check_if_is_directory(node->value);
	if (!is_file(node->value) && !search_valid_path(node->value, envp))
	{
		handle_node_value(node, envp, old_string);
		return ;
	}
	execute_command(node->value, envp, node);
}

void	check_and_execute_if_is_cmd(t_ast_node *node, char **envp)
{
	if (ft_split(node->value, ' ')[0])
	{
		if (search_valid_path(ft_split(node->value, ' ')[0], envp) == NULL)
		{
			printf("minishell: %s: command not found\n",
				ft_split(node->value, ' ')[0]);
			return ;
		}
	}
	if (is_directory(node->value))
	{
		printf("minishell: %s: Is a directory\n", node->value);
		return ;
	}
	else
		execute_command(node->value, envp, node);
}

void	execute_regular_cmd(t_ast_node *node, char **envp)
{
	char	*command_to_execute;

	if (node->type == NODE_COMMAND)
		command_to_execute = ft_split(node->value, ' ')[0];
	else
		command_to_execute = ft_strdup(node->value);
	if (ft_strchr(node->value, '$') != NULL)
	{
		if (node->type == NODE_COMMAND)
			execute_command(ft_split(node->value, ' ')[0], envp, node);
		else
			execute_command(node->value, envp, node);
	}
	else
	{
		if (ft_strchr(node->value, '/') != NULL)
			printf("zsh: %s: No such file or directory\n", node->value);
		else if (search_valid_path(command_to_execute, envp) == NULL)
		{
			printf("minishell: %s: command not found\n", command_to_execute);
			return ;
		}
		else
			execute_command(node->value, envp, node);
	}
}

int	verify_if_is_env_var(t_ast_node *node)
{
	char	*old_string;

	if (!node->value || node->value[0] == '\0')
		return (0);
	old_string = ft_strdup(node->value);
	node->value = process_env_var(node->value);
	if (ft_strcmp(old_string, node->value) != 0)
	{
		free(old_string);
		return (1);
	}
	free(old_string);
	return (0);
}
