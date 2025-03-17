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
	if (argv[1] && argv[2])
	{
		printf("cd: muitos argumentos\n");
		add_exitcode(1);
		return (0);
	}
	else if (((!argv[1] || argv[1][0] == '~') && chdir(getenv("HOME")) >= 0))
	{
		setenv("PWD", getcwd(NULL, 0), 1);
		add_exitcode(0);
		return (1);
	}
	if (chdir(argv[1]) >= 0)
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

void	update_env_copy(char ***env_copy, const char *new_var)
{
	int		i;
	size_t	var_len;
	char	*equal_sign;

	i = 0;
	equal_sign = ft_strchr(new_var, '=');
	if (equal_sign)
		var_len = equal_sign - new_var;
	else
		var_len = ft_strlen(new_var);
	while ((*env_copy)[i])
	{
		if (ft_strncmp((*env_copy)[i], new_var, var_len) == 0 &&
			(*env_copy)[i][var_len] == '=')
		{
			free((*env_copy)[i]);
			(*env_copy)[i] = ft_strdup(new_var);
			return ;
		}
		i++;
	}
	(*env_copy)[i] = ft_strdup(new_var);
	if (!(*env_copy)[i])
		return ;
	(*env_copy)[i + 1] = NULL;
}

int	export(char *argv[], char **envp)
{
	int		i2;
	char	*equal_pos;
	char	**tmp;
	char	*equal;

	i2 = 1;
	tmp = envp;
	if (!argv[1])
	{
		sort(tmp);
		while (*tmp)
		{
			equal = strchr(*tmp, '=');
			if (equal)
				printf("declare -x %.*s=\"%s\"\n",
					(int)(equal - *tmp), *tmp, equal + 1);
			else
				printf("declare -x %s\n", *tmp);
			tmp++;
		}
	}
	while (argv[i2])
	{
		update_env_copy(&envp, argv[i2]);
		equal_pos = strchr(argv[i2], '=');
		if (equal_pos)
		{
			*equal_pos = '\0';
			if (!equal_pos[1])
			{
				setenv(argv[i2], argv[i2 + 1], 1);
				i2++;
			}
			else
				setenv(argv[i2], equal_pos + 1, 1);
		}
		else
			setenv(argv[i2], "", 1);
		i2++;
	}
	return (0);
}

int	unset(char *argv[])
{
	int	i;

	i = 1;
	if (!argv[i])
	{
		printf("Uso: %s NOME_VARIAVEL\n", argv[0]);
		add_exitcode(1);
		return (1);
	}
	while (argv[i])
	{
		unsetenv(argv[i]);
		i++;
	}
	add_exitcode(0);
	return (1);
}
