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

void execute_command(char *cmd, char **envp)
{
    char **tokens;
    char *path;
    pid_t pid;

	tokens = ft_split(cmd, ' ');
    if (!tokens || !tokens[0]) {
        perror("Comando vazio\n");
        return;
    }
	path = search_valid_path(tokens[0], envp);
	pid = fork();
    if (pid < 0) {
        perror("fork command");
        return;
    }
    if (pid == 0) {
        if (execve(path, tokens, envp) == -1) {
            perror("execve");
            exit(127);
        }
        exit(0);
    }
    waitpid(pid, NULL, 0);
}

// void	execute_command(char *argv, char **envp, t_ast_node *node)
// {
// 	char	**command;
// 	char	*path;
// 	int	id;

// 	node = node;
// 	command = ft_split(argv, ' ');
// 	if (!command || !command[0])
// 	{
// 		printf("Not found");
// 	}

// 	path = search_valid_path(command[0], envp);
// 	id = fork();
// 	if (id == 0)
// 	{
// 		if (!path)
// 		{
// 			printf("invalid path\n");
// 			free(path);
// 			exit(EXIT_FAILURE);

// 		}
// 		if (execve(path, command, envp) == -1)
// 		{
// 			free(path);
// 			perror("execve failed.");
// 			exit(127);
// 		}
// 	} else 
// 		waitpid(id, NULL, 0);
// }
