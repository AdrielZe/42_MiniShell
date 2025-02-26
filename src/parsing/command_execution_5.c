/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/26 15:52:38 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	found_env_var(t_ast_node *node, char *old_string)
{
	return (ft_strcmp(old_string, node->value));
}

void	execute_valid_cmd(t_ast_node *node, char **envp, char *old_string, char *cmd)
{
	char	*env_result;
	char	*env_processed;
	char 	*temp;

	env_result = ft_strchr(node->value, '/');
	env_processed = ft_split(env_result, ' ')[0];
	temp = ft_strjoin(cmd, " ");
	node->value = ft_strjoin(temp, env_processed);
	check_if_is_cmd_or_dir(node, old_string, envp);
}

void execute_invalid_cmd(t_ast_node *node, char **envp, char *old_string, char *cmd)
{
	
}