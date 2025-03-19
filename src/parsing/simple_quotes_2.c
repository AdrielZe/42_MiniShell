/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_quotes_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:01:30 by marvin            #+#    #+#             */
/*   Updated: 2025/03/19 04:16:33 by victda-s         ###   ########.fr       */
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
