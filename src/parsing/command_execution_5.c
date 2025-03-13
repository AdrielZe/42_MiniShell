/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/27 00:39:47 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	found_env_var(t_ast_node *node, char *old_string)
{
	return (ft_strcmp(old_string, node->value));
}

void	execute_valid_cmd(t_ast_node *node, char **envp, char *cmd)
{
	char	*env_result;
	char	*env_processed;
	char	*temp;

	env_result = ft_strchr(node->value, '/');
	env_processed = ft_split(env_result, ' ')[0];
	temp = ft_strjoin(cmd, " ");
	node->value = ft_strjoin(temp, env_processed);
	check_if_is_cmd_or_dir(node, envp);
}

void	execute_invalid_cmd(t_ast_node *node, char **envp)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_split(node->value, ' ');
	while (arr[i])
	{
		if (ft_strchr(arr[i], '$') == NULL)
		{
			node->value = ft_strdup(arr[i]);
			check_if_is_cmd_or_dir(node, envp);
			free_array(arr);
			return ;
		}
		i++;
	}
	free_array(arr);
}

void	handle_found_env_var(t_ast_node *node, char **envp, char *cmd)
{
	char	*env_result;
	char	**env_processed;

	env_result = ft_strchr(node->value, '/');
	env_processed = ft_split(env_result, ' ');
	if (search_valid_path(cmd, envp) && node->type == NODE_COMMAND)
	{
		execute_valid_cmd(node, envp, cmd);
		free_env_and_array(env_result, env_processed);
		return ;
	}
	else if (!search_valid_path(cmd, envp) && node->type == NODE_COMMAND)
	{
		execute_invalid_cmd(node, envp);
		free_env_and_array(env_result, env_processed);
		return ;
	}
	else if (node->type == NODE_WORD)
	{
		check_if_is_cmd_or_dir(node, envp);
		free_array(env_processed);
		return ;
	}
	node->value = env_processed[0];
	check_if_is_cmd_or_dir(node, envp);
}
