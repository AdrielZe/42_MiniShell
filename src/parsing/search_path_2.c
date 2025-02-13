/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:27:34 by marvin            #+#    #+#             */
/*   Updated: 2025/02/13 19:02:13 by victda-s         ###   ########.fr       */
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

void	execute_command(char *cmd, char **envp, t_ast_node *node)
{
	char	**tokens;
	char	*path;
	pid_t	pid;

	tokens = ft_split(cmd, ' ');
	if (!tokens || !tokens[0])
		return (perror("Comando vazio\n"));
	path = search_valid_path(tokens[0], envp);
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		valid_outfile_and_path(cmd, node, path);
		if (execve(path, tokens, envp) == -1)
			exit(127);
		exit(0);
	}
	waitpid (pid, NULL, 0);
}
