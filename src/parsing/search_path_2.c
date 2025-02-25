/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:27:34 by marvin            #+#    #+#             */
/*   Updated: 2025/02/25 12:50:18 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

static void	valid_outfile_and_path(char *cmd, t_ast_node *node, char *path)
{
	if (node->outfile)
		dup2(node->outfile, STDOUT_FILENO);
	if (node->infile)
		dup2(node->infile, STDIN_FILENO);
	if (!path)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(" :command not found\n", STDERR_FILENO);
		exit(127);
	}
}

static char	*if_env_var(t_ast_node *node, char **tokens)
{
	char	*cmd;
	char	*expanded;
	int		i;

	i = 0;
	cmd = process_env_var(tokens[0]);
	if (node->type == NODE_ENV_VAR)
	{
		while (tokens[i])
		{
			if (ft_strchr(tokens[i], '$') != NULL)
			{
				expanded = process_env_var(tokens[i]);
				break ;
			}
			i++;
		}
		return (expanded);
	}
	return (cmd);
}

void	execute_command(char *cmd, char **envp,
			t_ast_node *node, int is_env_var)
{
	char	**tokens;
	char	*path;
	pid_t	pid;

	if (node->type == NODE_COMMAND)
	{
		tokens = split_with_quotes(cmd);
		if (!tokens || !tokens[0])
			return (perror("Comando vazio\n"));
		path = search_valid_path(tokens[0], envp);
		pid = fork();
		if (pid < 0)
			return ;
		path = search_valid_path(ft_split(cmd, ' ')[0], envp);
		if (pid == 0)
		{
			valid_outfile_and_path(cmd, node, path);
			if (execve(path, tokens, envp) == -1)
				exit(127);
			exit(0);
		}
		waitpid (pid, NULL, 0);
	} 
	else 
	{
		tokens = split_with_quotes(cmd);
		if (!tokens || !tokens[0])
			return (perror("Comando vazio\n"));
		path = search_valid_path(tokens[0], envp);
		pid = fork();
		if (pid < 0)
			return ;
		path = search_valid_path(ft_split(cmd, ' ')[0], envp);
		if (pid == 0)
		{
			valid_outfile_and_path(cmd, node, path);
			if (execve(path, tokens, envp) == -1)
				exit(127);
			exit(0);
		}
		waitpid (pid, NULL, 0);
	}
}
