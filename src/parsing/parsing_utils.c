/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:20:59 by marvin            #+#    #+#             */
/*   Updated: 2025/03/06 22:20:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	not_found_msg_and_free(t_ast_node *node, char *search_result,
					char **split_values, char *command_to_execute)
{
	printf("minishell: %s: command not found\n", command_to_execute);
	add_exitcode(127);
	if (node->type == NODE_COMMAND)
		free_split(split_values);
	else
		free(command_to_execute);
	free(search_result);
}

void	handle_env_var(t_ast_node *node, char **envp, char *old_string)
{
	if (ft_strcmp(old_string, node->value) != 0)
		check_and_execute_if_is_cmd(node, envp);
	else
		execute_regular_cmd(node, envp);
}

void	process_command_execution(t_ast_node *node,
			char **envp, char *old_string, char **split_result)
{
	if (if_cd(node->value, envp, node))
	{
		if (old_string)
			free(old_string);
		if (split_result)
			free_split(split_result);
		return ;
	}
	handle_env_var(node, envp, old_string);
	if (old_string)
		free(old_string);
	if (split_result)
		free_split(split_result);
}

void	free_env_and_array(char *env_result, char **env_processed)
{
	free(env_result);
	free_array(env_processed, array_len(env_processed));
}

void	process_local_array(char **temp, char **arr_not_envp)
{
	char	**local_arr;
	char	*old_temp;
	int		i;
	int		j;

	j = 0;
	while (arr_not_envp[j])
	{
		local_arr = ft_split(arr_not_envp[j], ' ');
		if (!local_arr)
		{
			free_array(arr_not_envp, array_len(arr_not_envp));
			return ;
		}
		i = 0;
		while (local_arr[i])
		{
			if (ft_strchr(local_arr[i], '$') == NULL)
				get_cmds_to_execute(&old_temp, temp, local_arr, i);
			i++;
		}
		free_array(local_arr, array_len(local_arr));
		j++;
	}
}
