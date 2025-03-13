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

void	update_node_value(t_ast_node *node, char *new_value)
{
	char	*old_value;

	old_value = node->value;
	node->value = ft_strdup(new_value);
	if (old_value)
		free(old_value);
}

void	process_valid_path(t_ast_node *node,
		char **value_to_search, char **envp)
{
	char	*valid_path;

	valid_path = search_valid_path(value_to_search[0], envp);
	if (!valid_path)
	{
		update_node_value(node, value_to_search[0]);
		free_array(value_to_search);
		check_and_execute_if_is_cmd(node, envp);
		return ;
	}
	free(valid_path);
	free_array(value_to_search);
	check_if_is_cmd_or_dir(node, envp);
}
