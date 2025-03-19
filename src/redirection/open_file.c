/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:35:00 by victda-s          #+#    #+#             */
/*   Updated: 2025/02/20 21:51:27 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <fcntl.h>
#include <unistd.h>

static char *space_tratament(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	str = ft_strtrim(str, " ");
	while(str[i] && str[i] != ' ')
		i++;
	tmp = ft_substr(str, 0, i);
	free(str);
	return (tmp);
}
int	open_stdout(char *file)
{
	int	fd;

	file = space_tratament(file);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	open_append(char *file)
{
	int	fd;

	file = space_tratament(file);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR, 0644);
	free(file);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	open_stdin(char *file)
{
	int	fd;

	file = space_tratament(file);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
	{
		perror("Erro ao abrir o arquivo");
		return (-2);
	}
	return (fd);
}
