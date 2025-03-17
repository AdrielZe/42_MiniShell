/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmds_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 01:09:05 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/16 23:11:43 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

t_heredoc_data	*get_heredoc_data(void)
{
	static t_heredoc_data	data = {NULL, NULL};

	return (&data);
}
char	*get_quoted_string(const char **s, char quote)
{
	const char	*start = *s;
	while (**s && **s != quote)
		(*s)++;
	if (**s == quote)
	{
		(*s)++;
		return (strndup(start, *s - start - 1));
	}
	return (NULL);
}
