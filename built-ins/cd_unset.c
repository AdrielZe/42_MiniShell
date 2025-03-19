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

#include "../headers/main.h"

int	cd(char *argv[])
{
	char	*cwd;

	if (argv[1] && argv[2])
	{
		printf("cd: many arguments\n");
		add_exitcode(1);
		return (0);
	}
	else if (((!argv[1] || argv[1][0] == '~') && chdir(getenv("HOME")) >= 0))
	{
		setenv("PWD", getcwd(NULL, 0), 1);//GETCWD MEMORY LEAK
		add_exitcode(0);
		return (1);
	}
	if (chdir(argv[1]) >= 0)
	{
		cwd = getcwd(NULL, 0);
		setenv("PWD", cwd, 1);
		add_exitcode(0);
		free(cwd);
		return (1);
	}
	else
	{
		perror("cd");
		add_exitcode(127);
	}
	return (0);
}

void	remove_env_var(char ***env_copy, const char *var_name)
{
	int		i;
	int		j;
	size_t	name_len;

	name_len = ft_strlen(var_name);
	i = 0;
	while ((*env_copy)[i])
	{
		if (ft_strncmp((*env_copy)[i], var_name, name_len) == 0 &&
				((*env_copy)[i][name_len] == '=' ||
				(*env_copy)[i][name_len] == '\0'))
		{
			free((*env_copy)[i]);
			j = i;
			while ((*env_copy)[j])
			{
				(*env_copy)[j] = (*env_copy)[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}

int	unset(char *argv[], char ***envp)
{
	int	i;

	i = 1;
	if (!argv[i])
	{
		printf("Use: %s variable_name\n", argv[0]);
		add_exitcode(1);
		return (1);
	}
	while (argv[i])
	{
		unsetenv(argv[i]);
		remove_env_var(envp, argv[i]);
		i++;
	}
	add_exitcode(0);
	return (1);
}
