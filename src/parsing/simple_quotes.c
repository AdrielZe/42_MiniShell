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


void execute_simple_quote_node(t_ast_node *node, char *cmd, char **envp)
{
	char **tokens;
	char *path;
	pid_t pid;
	char *built[1];

	built[0] = "PATH=built-ins";
	cmd = ft_strtrim(node->value, "'");
	if (!cmd)
		return;
	tokens = split_with_quotes(cmd);
	if (!tokens)
	{
		free(cmd);
		return;
	}
	path = search_valid_path(cmd, built);
	if (!path)
		path = search_valid_path(cmd, envp);
	if (!path)
	{
		free(cmd);
		free_array(tokens, array_len(tokens));
		return;
	}
	open_pid(&pid);
	if (pid == 0)
	{
		valid_outfile_and_path(cmd, node, path);
		free(cmd);
		if (execve(path, tokens, envp) == -1)
		exit(127);
		exit(0);
	}
	free(path);
	free(cmd);
	free_array(tokens, array_len(tokens));
	waitpid(pid, NULL, 0);
}
void	handle_simple_quote_node(t_ast_node *node, char **envp)
{
	if (!node->value || node->value[0] == '\0')
		return ;

	execute_simple_quote_node(node, node->value, envp);	
}