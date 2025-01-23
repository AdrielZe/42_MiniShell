/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:27:34 by marvin            #+#    #+#             */
/*   Updated: 2025/01/22 17:27:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/parsing.h"

void	exit_if_invalid_path(char **cmd)
{
	if (cmd && cmd[0])
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd("\n", 2);
	}
	free_cmd(cmd);
	exit(127);
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

char	*search_valid_path(char *cmd, char *envp)
{
	char		**paths;
	char		*current_path;	
	char		*current_path_and_command;
	int			j;

	j = 0;
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	paths = ft_split(envp, ':');
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

void	execute_command(char *argv, char *envp)
{
	char	**command;
	char	*path;

	command = ft_split(argv, ' ');
	if (!command || !command[0])
	{
		perror("command not found: ");
		exit(EXIT_FAILURE);
	}
	path = search_valid_path(command[0], envp);
	if (!path)
		exit_if_invalid_path(&command[0]);
	printf("Path found!");
	// if (execve(path, command, envp) == -1)
	// {
	// 	perror("execve failed.");
	// 	exit(127);
	// }
}