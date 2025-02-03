/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:27:34 by marvin            #+#    #+#             */
/*   Updated: 2025/02/03 20:21:11 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	execute_command(char **argv, char **envp)
{
	// char	**tokens;
	char	*path;
	pid_t	pid;

	// tokens = ft_split(*argv, ' ');
	// if (!tokens || !tokens[0])
	// {
	// 	perror("Comando vazio\n");
	// 	return ;
	// }
	path = search_valid_path(argv[0], envp);
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (execve(path, argv, envp) == -1)
		{
			perror("execve");
			exit(127);
		}
		exit(0);
	}
	waitpid (pid, NULL, 0);
}
