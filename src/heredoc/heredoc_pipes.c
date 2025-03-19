/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:57:59 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/19 09:21:48 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	protect_fork(pid_t *pid)
{
	if (*pid < 0)
	{
		perror("fork");
		return ;
	}
}

void	open_heredoc_pipe(int *pipefd, pid_t *pid)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	*pid = fork();
	if (*pid < 0)
	{
		perror("fork");
		return ;
	}
}
