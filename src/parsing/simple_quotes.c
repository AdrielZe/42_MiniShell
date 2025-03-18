/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:01:30 by marvin            #+#    #+#             */
/*   Updated: 2025/03/06 17:01:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <signal.h>

void	get_cmd(t_ast_node *node, char **cmd, char ***tokens)
{
	*tokens = split_with_quotes(node->value);
	if (!*tokens)
		return ;
	*cmd = *tokens[0];
}

void	if_not_path(char *cmd, char **tokens)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	add_exitcode(127);
	free_array(tokens);
}

void	free_elements_and_wait_child(char *path,
			char *cmd, char **tokens, int pid)
{
	free(path);
	free(cmd);
	free_array(tokens);
	waitpid(pid, NULL, 0);
}

void	execute_simple_quote_node(t_ast_node *node, char *cmd, char **envp)
{
	char	**tokens;
	char	*path;
	pid_t	pid;
	char	*built[1];
	int		status;

	built[0] = "PATH=built-ins";
	get_cmd(node, &cmd, &tokens);
	if (is_src_file(cmd) == 1)
	{
		free_array(tokens);
		return ;
	}
	path = search_valid_path(cmd, built);
	if (!path)
		path = search_valid_path(cmd, envp);
	if (!path)
	{
		handle_execution_failure(cmd, tokens);
		return ;
	}
	open_pid(&pid);
	set_signal_handler(sigint_cat_action);
	if (pid == 0)
		execute_child_process(cmd, path, tokens, envp);
	free_array(tokens);
	free(path);
	waitpid(pid, &status, 0);
	add_exitcode(WEXITSTATUS(status));
}

void	handle_simple_quote_node(t_ast_node *node, char **envp)
{
	char	*command_to_execute;
	char	**split_values;
	char	*search_result;
	char	**split_path;

	rmv_quotes_set_cmd(node, &split_values, &command_to_execute);
	search_result = search_valid_path(command_to_execute, envp);
	if (!node->value || node->value[0] == '\0')
		return ;
	if (ft_strchr(node->value, '/') != NULL)
	{
		if (control_command_execution_with_slash(&split_path,
				node, envp) == 1)
		{
			free(split_values);
			return ;
		}
		else if (not_result_msg_free(search_result,
				node, split_values, command_to_execute) == 1)
			return ;
		else
			execute_simple_quote_node(node, node->value, envp);
	}
	free_array(split_values);
	execute_simple_quote_node(node, node->value, envp);
}
