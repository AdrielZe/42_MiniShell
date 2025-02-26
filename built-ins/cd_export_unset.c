/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_export_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 00:05:03 by victda-s          #+#    #+#             */
/*   Updated: 2025/02/26 18:51:13 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

extern char	**environ;

int	cd(char *argv[])
{
	if(argv[2])
	{
		printf("cd: muitos argumentos\n");
		return (0);
	}
	else if(!argv[1])
	{
		if(chdir(getenv("HOME")))
			return (0);
	}
	else if(chdir(argv[1]) >= 0)
	{
		write(1, "--- by VICTDA-S\n", 16);
		return (1);
	}
	else	
		perror("cd");

}

int	export(char *argv[])
{
	char	**env;
	if (!argv[1]|| !ft_strchr(argv[1], '=')) {
		printf("Uso: %s NOME=VALOR\n", argv[0]);
		return (0);
	}
	env = ft_split(argv[1], '=');
	if (setenv(env[0], env[1], 1) != 0)
		perror("setenv");
	free(env[0]);
	free(env[1]);
	free(env);
	return (1);
}
