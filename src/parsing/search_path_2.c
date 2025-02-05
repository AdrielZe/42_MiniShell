/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:27:34 by marvin            #+#    #+#             */
/*   Updated: 2025/02/03 18:17:06 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	execute_command(char *cmd, char **envp)
{
	char	**tokens;
	char	*path;
	pid_t	pid;

	tokens = ft_split(cmd, ' ');
	if (!tokens || !tokens[0])
		return (perror("Comando vazio\n"));
	path = search_valid_path(tokens[0], envp);
	if (!path)
	{
		free(path);
		printf("command not found: %s\n", cmd);
		return ;
	}
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (execve(path, tokens, envp) == -1)
			exit(127);
		exit(0);
	}
	waitpid (pid, NULL, 0);
}
