/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 19:00:10 by marvin            #+#    #+#             */
/*   Updated: 2025/03/08 19:00:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	execute_command_for_word_node(char *path, char **tokens, char **envp)
{
	pid_t	pid;
	int		status;

	printf("Preguicoso assim?\n");
	open_pid(&pid);
	if (pid == 0)
	{
		valid_outfile_and_path(NULL, path);
		if (execve(path, tokens, envp) == -1)
		{
			perror("execve failed");
			exit(127);
		}
	}
	waitpid(pid, &status, 0);
	return (status);
}
