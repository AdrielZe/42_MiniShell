/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_direction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/03/05 19:43:04 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <sys/stat.h>

void	execute_cmd_or_word(t_ast_node *node,
		char *command_to_execute, char **envp)
{
	if (node->type == NODE_COMMAND)
		execute_command(command_to_execute, envp, node);
	else
		execute_command(node->value, envp, node);
}

void	print_not_found_msg_and_free(char *command_to_execute,
		t_ast_node *node, char **split_values)
{
	printf("minishell: %s: command not found\n", command_to_execute);
	if (command_to_execute)
		free(command_to_execute);
	if (node->type == NODE_COMMAND)
	{
		if (split_values)
			free(split_values);
	}
}

void	get_cmd_to_execute(t_ast_node *node,
		char ***split_values, char **command_to_execute)
{
	*split_values = ft_split(node->value, ' ');
	*command_to_execute = *split_values[0];
}

void	free_resources(t_ast_node *node,
		char **split_values, char *search_result)
{
	if (node->type == NODE_COMMAND)
		free_split(split_values);
	free(search_result);
}

void	get_cmds_to_execute(char **old_temp,
		char **temp, char **local_arr, int i)
{
	*old_temp = *temp;
	*temp = ft_strjoin(*temp, " ");
	*old_temp = *temp;
	*temp = ft_strjoin(*temp, local_arr[i]);
	free(*old_temp);
}
