/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:43:50 by victda-s          #+#    #+#             */
/*   Updated: 2025/02/24 23:31:05 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
int	main(int argc, char *argv[])
{
	char	pwd[256];

	if(getcwd(pwd, sizeof(pwd)))
		printf("%s   ---by VICTDA-S\n", pwd);
	else
		perror("error pwd");
	return (0);
}