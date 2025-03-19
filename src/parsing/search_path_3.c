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

void	redirect_io(t_ast_node *node)
{
	if (node->outfile)
	{
		dup2(node->outfile, STDOUT_FILENO);
		close(node->outfile);
	}
	if (node->infile)
	{
		dup2(node->infile, STDIN_FILENO);
		close(node->infile);
	}
}

void	execute_command(char *cmd, char **envp, t_ast_node *node)
{
	int	saved_stdin;
	int	saved_stdout;

	fflush(stdout);
	saved_stdin = dup(STDIN_FILENO);
	fflush(stdout);
	saved_stdout = dup(STDOUT_FILENO);
	fflush(stdout);
	redirect_io(node);
	if (node->type == NODE_COMMAND || node->type == NODE_HEREDOC)
		execute_node_command(node, cmd, envp);
	else if (node->type == NODE_WORD)
		execute_word_node(node, cmd, envp);
	else if (node->type == NODE_SIMPLE_QUOTE)
		execute_simple_quote_node(node, cmd, envp);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
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

char	*resolve_path(char *cmd, char **envp)
{
	char	*path;
	char	**path_split;
	char	*built[2];

	built[0] = PWD_PROJ;
	built[1] = NULL;
	path_split = ft_split(cmd, ' ');
	if (!path_split)
	{
		free_array(built);
		return (NULL);
	}
	path = search_valid_path(path_split[0], built);
	if (!path)
		path = search_valid_path(path_split[0], envp);
	free_array(path_split);
	return (path);
}

void	execute_command_for_node_function(char *path,
			char **tokens, char **envp)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		valid_outfile_and_path(tokens[0], path);
		if (execve(path, tokens, envp) == -1)
		{
			printf("minishell: %s: is a directory\n", tokens[0]);
			exit(127);
		}
		exit(0);
	}
	waitpid(pid, &status, 0);
	g_exit = WEXITSTATUS(status);
}
