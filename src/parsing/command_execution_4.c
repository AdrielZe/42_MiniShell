/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/03/19 09:08:30 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	cd(char *argv[]);
int	export(char *argv[], char **envp);
int	unset(char *argv[], char ***envp);

void	process_command(t_ast_node *node,
		char **envp, char *old_string, char **split_result)
{
	int	is_env_var;

	is_env_var = (split_result && ft_strchr(split_result[0], '$') != NULL);
	if (node->type != NODE_SIMPLE_QUOTE)
		node->value = process_env_var(node->value, 0);
	if (is_env_var)
		when_only_env_var(node, envp);
	else
		process_command_execution(node, envp, old_string, split_result);
	free_array(split_result);
	free(old_string);
}

void	handle_command_node(t_ast_node *node, char **envp)
{
	char	*old_string;
	char	**split_result;
	int		saved_stdin;

	saved_stdin = dup(STDIN_FILENO);
	if (node->outfile)
		dup2(node->outfile, STDOUT_FILENO);
	if (node->infile)
		dup2(node->infile, STDIN_FILENO);
	if (!node->value || node->value[0] == '\0')
		return ;
	split_result = ft_split(node->value, ' ');
	if (!split_result)
	{
		close(saved_stdin);
		return ;
	}
	old_string = ft_strdup(node->value);
	process_command(node, envp, old_string, split_result);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

int	check_if_is_directory(char *node_value)
{
	if (is_directory(node_value) == 0)
	{
		printf("minishell: %s: Is a directory\n", node_value);
		write_exitcode(126);
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
		free_array(split_cmd);
		return ;
	}
	else
	{
		handle_not_found_env_var(node, envp);
		free_array(split_cmd);
	}
}
