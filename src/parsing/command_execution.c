/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/01/24 13:06:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

void	execute_command(char *argv, char **envp)
{
	char	**command;
	char	*path;
	int		id;

	id = fork();
	command = ft_split(argv, ' ');
	path = search_valid_path(command[0], envp);
	if (id == 0)
	{
		if (!path)
		{
			printf("invalid path\n");
			free(path);
			exit(EXIT_FAILURE);
		}
		if (execve(path, command, envp) == -1)
		{
			free(path);
			perror("execve failed.");
			exit(127);
		}
	}
	else
		waitpid(id, NULL, 0);
}
