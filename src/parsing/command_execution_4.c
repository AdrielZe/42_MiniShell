/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/02/28 15:22:53 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	cd(char *argv[]);
int	export(char *argv[], char **envp);
int	unset(char *argv[]);

int	if_cd(char *cmd, char **envp, t_ast_node *node)
{
	char	**split_cmd;

	if (node->outfile)
		close(node->outfile);
	if (node->infile)
		close(node->infile);
	split_cmd = split_with_quotes(cmd);
	if (!split_cmd)
		perror("Comando vazio\n");
	else if (ft_strcmp(split_cmd[0], "cd") == 0)
	{
		cd(split_cmd);
		free_array(split_cmd, array_len(split_cmd));
		return (1);
	}
	else if (ft_strcmp(split_cmd[0], "export") == 0)
	{
		export(split_cmd, envp);
		free_array(split_cmd, array_len(split_cmd));
		return (1);
	}
	else if (ft_strcmp(split_cmd[0], "unset") == 0)
	{
		unset(split_cmd);
		free_array(split_cmd, array_len(split_cmd));
		return (1);
	}
	free_array(split_cmd, array_len(split_cmd));
	return (0);
}

void	handle_command_node(t_ast_node *node, char **envp)
{
	char	*old_string;
	int		is_env_var;
	char	**split_result;

	if (!node->value || node->value[0] == '\0')
		return ;
	split_result = ft_split(node->value, ' ');
	is_env_var = (split_result && ft_strchr(split_result[0], '$') != NULL);
	old_string = ft_strdup(node->value);
	if (node->type != NODE_SIMPLE_QUOTE)
		node->value = process_env_var(node->value);
	if (is_env_var)
		when_only_env_var(node, envp);
	else
		process_command_execution(node, envp, old_string, split_result);
}

int	check_if_is_directory(char *node_value)
{
	if (is_directory(node_value) == 0)
	{
		printf("minishell: %s: Is a directory\n", node_value);
		return (0);
	}
	return (1);
}

void	check_if_is_cmd_or_dir(t_ast_node *node, char **envp)
{
	if (ft_strchr(node->value, '/') != NULL)
	{
		printf("zsh: %s: No such file or directory\n", node->value);
	}
	else
		execute_command(node->value, envp, node);
}

void	handle_node_value(t_ast_node *node, char **envp, char *old_string)
{
	char	**split_cmd;

	split_cmd = ft_split(node->value, ' ');
	if (found_env_var(node, old_string) == 1)
	{
		handle_found_env_var(node, envp, old_string);
		free_array(split_cmd, array_len(split_cmd));
		return ;
	}
	else
	{
		handle_not_found_env_var(node, envp);
		free_array(split_cmd, array_len(split_cmd));
	}
}
