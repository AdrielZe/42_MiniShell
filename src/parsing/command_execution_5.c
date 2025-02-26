/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/26 17:08:39 by asilveir         ###   ########.fr       */
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
			return ;
		}
		i++;
	}
}

void	handle_found_env_var(t_ast_node *node, char **envp, char *cmd)
{
	char	*env_result;
	char	*env_processed;

	env_result = ft_strchr(node->value, '/');
	env_processed = ft_split(env_result, ' ')[0];
	if (search_valid_path(cmd, envp) && node->type == NODE_COMMAND)
	{
		execute_valid_cmd(node, envp, cmd);
		return ;
	}
	else if (!search_valid_path(cmd, envp) && node->type == NODE_COMMAND)
	{
		execute_invalid_cmd(node, envp);
		return ;
	}
	else if (node->type == NODE_WORD)
	{
		check_if_is_cmd_or_dir(node, envp);
		return ;
	}
	node->value = env_processed;
	check_if_is_cmd_or_dir(node, envp);
}
