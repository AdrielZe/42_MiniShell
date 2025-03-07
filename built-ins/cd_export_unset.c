/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 00:05:03 by victda-s          #+#    #+#             */
/*   Updated: 2025/02/26 20:43:08 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "../headers/main.h"

static void	sort(char **arr)
{
	int		swapped;
	int		i;
	int		n;
	char	*temp;

	n = 0;
	while (arr[n])
		n++;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (i < n - 1)
		{
			if (ft_strcmp(arr[i], arr[i + 1]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				swapped = 1;
			}
			i++;
		}
	}
}
int	cd(char *argv[])
{
	char *cwd; 

	if(argv[1] && argv[2])
	{
		printf("cd: muitos argumentos\n");
		add_exitcode(1);
		return (0);
	}
	else if(!argv[1] && chdir(getenv("HOME")) >= 0)
	{
		add_exitcode(0);
		return (1);
	}
	if(chdir(argv[1]) >= 0)
	{
		write(1, "--- by VICTDA-S\n", 16);
		setenv("PWD", getcwd(NULL, 0), 1);
		add_exitcode(0);
		return (1);
	}
	else
	{
		perror("cd");
		add_exitcode(127);
	}
	return (0);
}

int	export(char *argv[], char **envp)
{
	char	**env;

	if(!argv[1])
	{
		sort(envp);
		while(*envp)
			printf("declare -x %s\n", *envp++);
		add_exitcode(0);
		return (1);
	}
	if (!argv[1]|| !ft_strchr(argv[1], '='))
	{
		printf("Uso: %s NOME=VALOR\n", argv[0]);
		add_exitcode(1);
		return (1);
	}
	env = ft_split(argv[1], '=');
	if (setenv(env[0], env[1], 1) != 0)
		perror("setenv");
	free(env[0]);
	free(env[1]);
	free(env);
	add_exitcode(0);
	return (1);
}

int	unset(char *argv[])
{
	int	i;

	i = 1;
	if(!argv[i])
	{
		printf("Uso: %s NOME_VARIAVEL\n", argv[0]);
		add_exitcode(1);
		return (1);
	}
	while(argv[i])
	{
		unsetenv(argv[i]);
		i++;
	}
	add_exitcode(0);
	return (1);
}
