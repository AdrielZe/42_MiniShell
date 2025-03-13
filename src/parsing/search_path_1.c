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

#include "../headers/main.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	paths = NULL;
}

static int	search_for_path_index(char **envp)
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
		return (NULL);
	while (paths && paths[j])
	{
		current_path = ft_strjoin(paths[j], "/");
		current_path_and_command = ft_strjoin(current_path, cmd);
		free(current_path);
		if (access(current_path_and_command, F_OK | X_OK) == 0)
			return (free_paths(paths), current_path_and_command);
		free(current_path_and_command);
		j++;
	}
	free_paths(paths);
	return (NULL);
}
