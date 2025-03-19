/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_exitcode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 20:32:09 by victda-s          #+#    #+#             */
/*   Updated: 2025/03/19 19:14:00 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	add_exitcode(int status)
{
	char	*status_char;

	status_char = ft_itoa(status);
	if (!status_char)
		return ;
	setenv("EXITCODEMINISHELL", status_char, 1);
	free(status_char);
}

void	open_exitcode(void)
{
	int		fd;
	int		bytes_read;
	char	buffer[256];

	fd = open_stdin(".exitcode");
	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read)
	{
		buffer[bytes_read] = '\0';
		setenv("EXITCODEMINISHELL", buffer, 1);
	}
	close(fd);
}

void	write_exitcode(int exitcode)
{
	int		fd;
	char	*str_exitcode;

	fd = open_stdout(".exitcode");
	str_exitcode = ft_itoa(exitcode);
	write(fd, str_exitcode, ft_strlen(str_exitcode));
	free(str_exitcode);
	close(fd);
}
