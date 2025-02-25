/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/25 15:33:52 by asilveir         ###   ########.fr       */
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
	char	*old_string;
	int is_env_var;

	is_env_var = 0;
	if (node->type == NODE_HEREDOC)
	{
		*delimiters = get_all_delimiters(node);
		handle_heredoc(node, envp);
	}
	else if (node->type == NODE_WORD)
	{
		if (ft_strchr(node->value, '$') != NULL)
			is_env_var = 1;
		if (!node->value || node->value[0] == '\0')
			return ;
		old_string = ft_strdup(node->value);
		node->value = process_env_var(node->value);
		if (is_env_var == 1)
		{
			printf("checking and executing\n");
			when_only_env_var(node, envp, old_string);
		}
		else if (ft_strcmp(old_string, node->value) != 0)
		{
			check_and_execute_if_is_cmd(node, envp);
			
		}
		else
		{	
			printf("checking\n");
			execute_regular_cmd(node, envp);
			free(old_string);
		}
	}
	else if (node->type == NODE_COMMAND)
	{
		if (!node->value || node->value[0] == '\0')
			return ;
		if (ft_strchr(node->value, '$') != NULL)
			is_env_var = 1;
		old_string = ft_strdup(node->value);
		node->value = process_env_var(node->value);
		if (is_env_var == 1)
			when_only_env_var(node, envp, old_string);
		else if (ft_strcmp(old_string, node->value) != 0)
		{
			check_and_execute_if_is_cmd(node, envp);
		}
		else
		{	
			execute_regular_cmd(node, envp);
			free(old_string);
		}
	}
}
