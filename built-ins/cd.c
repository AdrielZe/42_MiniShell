/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 00:05:03 by victda-s          #+#    #+#             */
/*   Updated: 2025/02/25 01:50:19 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
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
		return (0);
	}
	else	
		perror("cd");

}