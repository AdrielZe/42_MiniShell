/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:08:46 by victda-s          #+#    #+#             */
/*   Updated: 2025/03/17 16:04:26 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "../libft/libft.h"

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
			((*env_copy)[i][var_len] == '=' || (*env_copy)[i][var_len] == '\0'))
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

void	print_export(char **envp, char *argv[])
{
	char	*equal;
	char	**tmp;

	tmp = envp;
	if (!argv[1])
	{
		sort(tmp);
		while (*tmp)
		{
			equal = ft_strchr(*tmp, '=');
			if (equal)
				printf("declare -x %.*s=\"%s\"\n",
					(int)(equal - *tmp), *tmp, equal + 1);
			else
				printf("declare -x %s\n", *tmp);
			tmp++;
		}
	}
}

int	export(char *argv[], char **envp)
{
	int		i;
	char	*equal_pos;

	i = 1;
	print_export(envp, argv);
	while (argv[i])
	{
		update_env_copy(&envp, argv[i]);
		equal_pos = ft_strchr(argv[i], '=');
		if (equal_pos)
		{
			*equal_pos = '\0';
			if (!equal_pos[1])
			{
				setenv(argv[i], argv[i + 1], 1);
				i++;
			}
			else
				setenv(argv[i], equal_pos + 1, 1);
		}
		else
			setenv(argv[i], "", 1);
		i++;
	}
	return (0);
}
