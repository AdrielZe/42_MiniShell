/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:27:34 by marvin            #+#    #+#             */
/*   Updated: 2025/01/29 16:03:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/parsing.h"

void	exit_if_invalid_path(char **cmd)
{
	if (cmd && cmd[0])
	{
		ft_putstr_fd("hereeee ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
	}
	free_cmd(cmd);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*search_valid_path(char *cmd, char **envp)
{
	char		**paths;
	char		*current_path;	
	char		*current_path_and_command;
	int			i;
	int			j;

	j = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	i = search_for_path_index(envp);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		free_paths(paths);
	while (paths && paths[j])
	{
		current_path = ft_strjoin(paths[j], "/");
		current_path_and_command = ft_strjoin(current_path, cmd);
		free(current_path);
		if (access(current_path_and_command, F_OK | X_OK) == 0)
			return (current_path_and_command);
		free(current_path_and_command);
		j++;
	}
	free_paths(paths);
	return (NULL);
}

int	search_for_path_index(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			break ;
		i++;
	}
	return (i);
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			free(cmd[i]);
			i++;
		}
		free(cmd);
	}
}

void	execute_command(char *argv, char **envp)
{
	char	**command;
	char	*path;
	int	id;
	id = fork();


	command = ft_split(argv, ' ');
	// if (ft_strchr(argv, '\0'))
	// {
	// printf("argv: %s\n", );
	// 	printf("space found");
	// }
	if (!command || !command[0])
	{
		printf("Not found");
	}

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
	} else 
		waitpid(id, NULL, 0);
}

void	execute_piped_command(t_ast_node *node, char **envp)
{
	int		fd[2];
	int		id;
	char	*argv;
	int status;

	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	id = fork();
	if (id == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		argv = parse_commands(node->left, envp);
		if (ft_isalnum(argv[0]) == 0)
			execute_command(argv, envp);
		exit(EXIT_SUCCESS);
	}
	else if (id > 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(id, &status, 0);
		parse_commands(node->right, envp);
		exit(EXIT_SUCCESS);
	}
}