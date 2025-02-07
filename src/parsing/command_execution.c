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

#include "../headers/main.h"

static void	left_process(int *pipe, t_ast_node *node, char **envp)
{
	if (dup2(pipe[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 left");
		exit(1);
	}
	close(pipe[0]);
	close(pipe[1]);
	parse_commands(node->left, envp);
	exit(0);
}

static void right_process(int *pipe, t_ast_node *node, char **envp, char *outfile)
{
    int fd;

	fd = 0;
    if (dup2(pipe[0], STDIN_FILENO) == -1)
    {
        perror("dup2 right");
        exit(1);
    }
    if (outfile)
    {
		fd = check_outfile(node, fd);
        if (dup2(fd, STDOUT_FILENO) == -1)
        {
            perror("dup2 outfile");
            close(fd);
            exit(1);
        }
        close(fd);
    }

    close(pipe[0]);
    close(pipe[1]);
    parse_commands(node->right, envp);
    exit(0);
}

static void	open_left_pipe(int *pipefd, pid_t *pid_left)
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	*pid_left = fork();
	if (*pid_left < 0)
	{
		perror("fork left");
		return ;
	}
}

static void	open_right_pipe(pid_t *pid_right)
{
	*pid_right = fork();
	if (*pid_right < 0)
	{
		perror("fork right");
		return ;
	}
}

void parse_commands(t_ast_node *node, char **envp)
{
    pid_t pid_left, pid_right;
    int pipefd[2];

    if (!node)
        return;

    if (node->type == NODE_PIPE)
    {
        open_left_pipe(pipefd, &pid_left);
        if (pid_left == 0)
            left_process(pipefd, node, envp);
        waitpid(pid_left, NULL, 0);
        open_right_pipe(&pid_right);
        if (pid_right == 0)
            right_process(pipefd, node, envp, node->right->outfile);
        close(pipefd[0]);
        close(pipefd[1]);
        waitpid(pid_left, NULL, 0);
        waitpid(pid_right, NULL, 0);
    }
    else if (node->type == NODE_COMMAND)
    {
        execute_command(node->value, envp, node);
    }
}
