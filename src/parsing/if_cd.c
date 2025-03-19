/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:06:54 by marvin            #+#    #+#             */
/*   Updated: 2025/03/19 09:08:20 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

int	cd(char *argv[]);
int	export(char *argv[], char **envp);
int	unset(char *argv[], char ***envp);

int	if_cd(char *cmd, char **envp)
{
	char	**split_cmd;

	split_cmd = split_with_quotes(cmd);
	if (!split_cmd)
		perror("Comando vazio\n");
	else if (ft_strcmp(split_cmd[0], "cd") == 0)
	{
		cd(split_cmd);
		free_array(split_cmd);
		return (1);
	}
	else if (ft_strcmp(split_cmd[0], "export") == 0)
	{
		export(split_cmd, envp);
		free_array(split_cmd);
		return (1);
	}
	else if (ft_strcmp(split_cmd[0], "unset") == 0)
	{
		unset(split_cmd, &envp);
		free_array(split_cmd);
		return (1);
	}
	free_array(split_cmd);
	return (0);
}
