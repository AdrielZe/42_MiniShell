/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:07:19 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/19 19:14:05 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

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
	char	*cmd_execute;

	if (check_if_is_directory(node->value) == 0)
		return ;
	cmd_execute = search_valid_path(node->value, envp);
	if (!is_file(node->value))
	{
		if (!cmd_execute)
		{
			if (ft_strchr(node->value, '/'))
				printf("minishell: %s: No such file or directory\n",
					node->value);
			else
				handle_command_node(node, envp);
			return ;
		}
		free(cmd_execute);
		return ;
	}
	free(cmd_execute);
	execute_command(node->value, envp, node);
}
