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

void	not_found_msg_and_free(t_ast_node *node, char *search_result, char **split_values, char *command_to_execute)
{
	printf("minishell: %s: command not found\n", command_to_execute);
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

void	process_command_execution(t_ast_node *node, char **envp, char *old_string, char **split_result)
{
	if (if_cd(node->value, envp, node))
	{
		free(old_string);
		free_split(split_result);
		return ;
	}
	handle_env_var(node, envp, old_string);
	free(old_string);
	free_split(split_result);
}

void	free_env_and_array(char *env_result, char **env_processed)
{
	free(env_result);
	free_array(env_processed, array_len(env_processed));
}