/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/03/19 04:38:33 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <sys/stat.h>

void	wait_for_processes(pid_t pid_left, pid_t pid_right, int *status)
{
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, status, 0);
	//Talvez falte o exitcode aqui, ou não
}

int	should_wait_left_process(t_ast_node *node,
		pid_t pid_left, int *status)
{
	if (node->left && node->left->value
		&& ft_strcmp(node->left->value, "<<") == 0)
	{
		waitpid(pid_left, status, 0);
	}
	return (WIFEXITED(*status) && WEXITSTATUS(*status) == 130);
}

void	handle_right_process(pid_t pid_right,
		int *pipefd, t_ast_node *node, char **envp)
{
	if (pid_right == 0)
	{
		right_process(pipefd, node, envp);
	}
	close_pipefd(pipefd);
}

void	open_pid(int *pid)
{
	*pid = fork();
	if (*pid < 0)
		return ;
}
