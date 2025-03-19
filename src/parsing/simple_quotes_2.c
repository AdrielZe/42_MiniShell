/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_quotes_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:01:30 by marvin            #+#    #+#             */
/*   Updated: 2025/03/19 06:56:15 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <signal.h>

int	is_src_file(char *cmd)
{
	if (ft_strcmp(cmd, "minishell") == 0)
	{
		printf("minishell: minishell: command not found\n");
		write_exitcode(127);
		return (1);
	}
	return (0);
}

void	handle_execution_failure(char *cmd, char **tokens)
{
	if_not_path(cmd, tokens);
}

void	execute_child_process(char *cmd, char *path, char **tokens, char **envp)
{
	valid_outfile_and_path(cmd, path);
	if (execve(path, tokens, envp) == -1)
	{
		perror("execve failed\n");
		exit(127);
	}
	exit(0);
}

void	execute_simple_quote_node(t_ast_node *node, char *cmd, char **envp)
{
	char	**tokens;
	char	*path;
	pid_t	pid;
	char	*built[1];
	int		status;

	built[0] = PWD_PROJ;
	get_cmd(node, &cmd, &tokens);
	if (is_src_file(cmd) == 1)
	{
		free_array(tokens);
		return ;
	}
	path = search_valid_path(cmd, built);
	if (control_path(&path, cmd, envp, tokens) == 1)
		return ;
	open_pid(&pid);
	set_signal_handler(sigint_cat_action);
	if (pid == 0)
		execute_child_process(cmd, path, tokens, envp);
	free_array(tokens);
	free(path);
	waitpid(pid, &status, 0);
	if (node->lastcmd)
		write_exitcode(WEXITSTATUS(status));
}