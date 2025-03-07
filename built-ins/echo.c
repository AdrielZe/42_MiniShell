/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:41:33 by victda-s          #+#    #+#             */
/*   Updated: 2025/02/26 13:53:16 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/libft.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	i;
	int new_line;

	i = 1;
	new_line = 1;
	if(!argv[1])
		return (0);
	if(ft_strnstr(argv[1], "-n", 2))
	{
		new_line = 0;
		i++;
	}
	while(argv[i])
	{
		printf("%s", argv[i]);
		if(argv[i+1])
			printf(" ");
		i++;
	}
	printf("   ---by VICTDA-S");
	if(new_line)
		printf("\n");
	exit (0);
}
int	export(char *argv[])
{
	char	**env;
	if (argv[2]|| !ft_strchr(argv[1], '=')) {
		printf("Uso: %s NOME=VALOR\n", argv[0]);
		return (1);
	}
	env = ft_split(argv[1], '=');
	if (setenv(env[0], env[1], 1) != 0)
		perror("setenv");
	printf("%s=%s\n", env[0], env[1]);
	free(env[0]);
	free(env[1]);
	free(env);
	return (0);
}