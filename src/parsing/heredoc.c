/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:41:35 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/11 21:14:07 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <fcntl.h>

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

void	read_heredoc(int *pipefd, char *delimiter)
{
	char	*input;

	close(pipefd[0]);
	while (1)
	{
		input = readline("heredoc> ");
		if (!input || !ft_strcmp(input, delimiter))
		{
			free(input);
			break ;
		}
		write(pipefd[1], input, ft_strlen(input));
		write(pipefd[1], "\n", 1);
		free(input);
	}
	close(pipefd[1]);
	exit(0);
}

void	execute_command_with_heredoc(int *pipefd,
			pid_t pid, t_ast_node *node, char **envp)
{
	char	**args;
	int	stdin_copy;

	stdin_copy = dup(STDIN_FILENO);
	args = malloc(2 * sizeof(char *));
	if (!args)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	args[0] = node->left->value;
	args[1] = NULL;
	search_valid_path(node->left->value, envp);
	waitpid(pid, NULL, 0);
	close(pipefd[1]);
	pid = fork();
	protect_fork(pipefd);
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_command(node->left->value, envp, node);
		exit(1);
	}
	dup2(stdin_copy, STDIN_FILENO);
	close(pipefd[0]);
	waitpid(pid, NULL, 0);
	free(args);
}

int handle_heredoc(t_ast_node *node, char **envp)
{
    int fd;

    // Aqui você precisa abrir um arquivo temporário ou outro mecanismo para armazenar o conteúdo do heredoc
    // Por exemplo, você pode gravar o conteúdo em um arquivo temporário e retornar o fd
    fd = open("/tmp/heredoc_temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1)
    {
        perror("Failed to open heredoc file");
        exit(1);
    }

    // Aqui você deve ler as entradas do usuário até o delimitador "eof" e gravar no arquivo
    char *line;
    while (1)
    {
        printf("heredoc> ");
        line = get_next_line(STDIN_FILENO);  // Supondo que você tenha uma função que leia a entrada
        if (!line || strcmp(line, node->value) == 0)
        {
            free(line);
            break;
        }
        write(fd, line, strlen(line));
        free(line);
    }
    return fd;
}
