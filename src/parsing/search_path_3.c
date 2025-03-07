/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:27:56 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/05 23:41:37 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	execute_command(char *cmd, char **envp,
	t_ast_node *node)
{
	if (node->outfile)
		dup2(node->outfile, STDOUT_FILENO);
	if (node->infile)
		dup2(node->infile, STDIN_FILENO);
	if (node->type == NODE_COMMAND)
		execute_node_command(node, cmd, envp);
	else if (node->type == TOKEN_WORD)
		execute_word_node(node, cmd, envp);
	else if (node->type == NODE_SIMPLE_QUOTE)
		execute_simple_quote_node(node, cmd, envp);
}

void	setup_tokens_and_commands(t_ast_node *node, char ***tokens,
		char **cmd, char ***cmd_to_split)
{
	*tokens = split_with_quotes(*cmd);
	if (node->type != NODE_SIMPLE_QUOTE)
	{
		*cmd = if_env_var(node, *tokens);
		*cmd_to_split = ft_split(*cmd, ' ');
	}
	else
	{
		*cmd = node->value;
		*cmd_to_split = ft_split(*cmd, ' ');
	}
	if (!*cmd_to_split)
		return ;
}

void	open_pid(int *pid)
{
	*pid = fork();
	if (*pid < 0)
		return ;
}

char	*resolve_path(char *cmd, char **envp)
{
	char	*path;
	char	**path_split;
	char	*built[2];

	built[0] = "PATH=built-ins";
	built[1] = NULL;
	path_split = ft_split(cmd, ' ');
	if (!path_split)
		return (NULL);
	path = search_valid_path(path_split[0], built);
	if (!path)
		path = search_valid_path(path_split[0], envp);
	free_array(path_split, array_len(path_split));
	return (path);
}

void	execute_command_for_node_function(char *path,
			char **tokens, char **envp, t_ast_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		valid_outfile_and_path(tokens[0], node, path);
		if (execve(path, tokens, envp) == -1)
			exit(127);
		exit(0);
	}
	waitpid(pid, NULL, 0);
}
