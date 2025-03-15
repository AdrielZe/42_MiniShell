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
	int	new_line;

	i = 1;
	new_line = 1;
	if (!argv[1])
	{
		printf("\n");
		exit (0);
	}
	if (ft_strnstr(argv[1], "-n", 2))
	{
		new_line = 0;
		i++;
	}
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	printf("   ---by VICTDA-S");
	if (new_line)
		printf("\n");
	exit (0);
}
