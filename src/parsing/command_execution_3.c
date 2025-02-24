/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/24 18:46:01 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <sys/stat.h>

void	handle_command_node(t_ast_node *node, char **envp)
{
	char	old_char;
	char	*old_string;

	if (!node->value || node->value[0] == '\0')
		return ;
	old_char = node->value[0];
	old_string = ft_strdup(node->value);
	node->value = process_env_var(node->value);
}

void	when_only_env_var(t_ast_node *node, char **envp, char *old_string)
{
	if (is_directory(node->value))
	{
		printf("minishell: %s: Is a directory\n", node->value);
		return ;
	}
	if (!is_file(node->value) && !search_valid_path(node->value, envp))
	{
		if (ft_strcmp(old_string, node->value) != 0)
		{
			if (ft_strchr(node->value, '/') != NULL)
				printf("zsh: %s: No such file or directory\n", node->value);
			else
				execute_command(node->value, envp, node, 1);
		}
		else
			return ;
		return ;
	}
	execute_command(node->value, envp, node, 1);
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
		execute_command(node->value, envp, node, 0);
}

void	execute_regular_cmd(t_ast_node *node, char **envp)
{
	if (ft_strchr(node->value, '$') != NULL)
		execute_command(ft_split(node->value, ' ')[0], envp, node, 1);
	else
	{
		if (ft_strchr(node->value, '/') != NULL)
			printf("zsh: %s: No such file or directory\n", node->value);
		else if (search_valid_path(ft_split(node->value, ' ')[0], envp) == NULL)
		{
			printf("minishell: %s: command not found\n",
				ft_split(node->value, ' ')[0]);
			return ;
		}
		else
			execute_command(node->value, envp, node, 0);
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
