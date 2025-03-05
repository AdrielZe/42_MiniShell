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

static int	if_cd(char *cmd, char **envp, t_ast_node *node)
{
	char	**split_cmd;

	split_cmd = split_with_quotes(cmd);
	if (!split_cmd)
		perror("Comando vazio\n");
	else if (ft_strcmp(split_cmd[0], "cd") == 0)
	{
		if (cd(split_cmd))
			return (1);
	}
	else if (ft_strcmp(split_cmd[0], "export") == 0)
	{
		if (export(split_cmd, envp))
			return (1);
	}
	else if (ft_strcmp(split_cmd[0], "unset") == 0)
	{
		if (unset(split_cmd))
			return (1);
	}
	if (node->outfile)
		close(node->outfile);
	if (node->infile)
		close(node->infile);
	return (0);
}
void	handle_command_node(t_ast_node *node, char **envp)
{
	char	*old_string;
	int		is_env_var;
	char	**split_result;

	is_env_var = 0;
	if (!node->value || node->value[0] == '\0')
		return ;
	split_result = ft_split(node->value, ' ');
	if (split_result && ft_strchr(split_result[0], '$') != NULL)
		is_env_var = 1;
	old_string = ft_strdup(node->value);
	node->value = process_env_var(node->value);
	if (is_env_var == 1)
		when_only_env_var(node, envp, old_string);
	else if (ft_strcmp(old_string, node->value) != 0)
		check_and_execute_if_is_cmd(node, envp);
	else
	{
		// printf("cmddddddddddddd: %s\n", node->value);
		// printf("%s\n", node->value);
		if(if_cd(node->value, envp, node))
			return ;
		execute_regular_cmd(node, envp);
	}
	free(old_string);
	if (split_result)
		free_split(split_result);
}

void	check_if_is_directory(char *node_value)
{
	if (is_directory(node_value))
	{
		printf("minishell: %s: Is a directory\n", node_value);
		return ;
	}
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
	char	*cmd;
	char	**arr;

	cmd = NULL;
	if (found_env_var(node, old_string))
	{
		if (node->type == NODE_COMMAND)
		{
			cmd = ft_split(node->value, ' ')[0];
		}
		else if (node->type == NODE_WORD)
			cmd = node->value;
		handle_found_env_var(node, envp, old_string);
		return ;
	}
	else
		handle_not_found_env_var(node, envp, arr);
}
