/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/25 19:45:26 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	handle_command_node(t_ast_node *node, char **envp)
{
	char	*old_string;
	int		is_env_var;

	is_env_var = 0;
	if (!node->value || node->value[0] == '\0')
		return ;
	if (ft_strchr(node->value, '$') != NULL)
		is_env_var = 1;
	old_string = ft_strdup(node->value);
	node->value = process_env_var(node->value);
	if (is_env_var == 1)
	{
		printf("aquiiiii\n");
		when_only_env_var(node, envp, old_string);
	}
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

void	check_if_is_directory(char *node_value)
{
	if (is_directory(node_value))
	{
		printf("minishell: %s: Is a directory\n", node_value);
		return ;
	}
}

void	check_if_is_cmd_or_dir(t_ast_node *node, char *old_string, char **envp)
{
	if (ft_strchr(node->value, '/') != NULL)
	{
		printf("zsh: %s: No such file or directory\n", node->value);
	}
	else
		execute_command(node->value, envp, node, 1);
}
void	handle_node_value(t_ast_node *node, char **envp, char *old_string)
{
	char	*env_result;
	char	*env_processed;
	char	*cmd;
	char	*temp;
	char	**arr;
	int i = 0;

	if (ft_strcmp(old_string, node->value) != 0)
	{
		if (node->type == NODE_COMMAND)
			cmd = ft_split(node->value, ' ')[0];
		else if (node->type == NODE_WORD)
			cmd = node->value;
		env_result = ft_strchr(node->value, '/');
		env_processed = ft_split(env_result, ' ')[0];
		if (search_valid_path(cmd, envp) && node->type == NODE_COMMAND)
		{
			printf("entrou no if\n");
			temp = ft_strjoin(cmd, " ");
			node->value = ft_strjoin(temp, env_processed);
			check_if_is_cmd_or_dir(node, old_string, envp);
			return ;
		}
		else if (!search_valid_path(cmd, envp) && node->type == NODE_COMMAND)
		{
			arr = ft_split(node->value, ' ');
			while (arr[i])
			{
				if (ft_strchr(arr[i], '$') == NULL)
				{
					node->value = ft_strdup(arr[i]);
					check_if_is_cmd_or_dir(node, old_string, envp);
				}
				return ;
			}
		}
		else if (node->type == NODE_WORD)
		{
			check_if_is_cmd_or_dir(node, old_string, envp);
			return ;
		}
		printf("nao entrou no if\n");
		node->value = env_processed;
		check_if_is_cmd_or_dir(node, old_string, envp);
	}
	else
	{
		printf("desenvolvendo\n");
		// if(search_valid_path(ft_split(node->value, ' ')[0], envp))
		// {
			
		// }
	}
}