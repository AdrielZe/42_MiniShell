/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:35:00 by victda-s          #+#    #+#             */
/*   Updated: 2025/02/11 13:13:21 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../headers/main.h"

int	open_stdout(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	open_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR, 0644);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	open_stdin(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	check_outfile(t_ast_node *node, int fd)
{
	if (node->right->outfile_type == NODE_REDIRECT_OUT)
		fd = open_stdout(node->right->outfile);
	else
		fd = open_append(node->right->outfile);
	node->outfile = NULL;
	return (fd);
}
