/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_if.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:36:14 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/15 12:38:42 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/main.h"

int	count_if(size_t *count, const char *s, char c)
{
	const char	*start;
	char		quote;

	start = s;
	if (*s == '"' || *s == '\'')
	{
		quote = *s++;
		while (*s && *s != quote)
			s++;
		if (*s)
			s++;
		(*count)++;
	}
	else if (*s++ == '|')
		(*count)++;
	else
	{
		while (*s && *s != c && *s != '|' && *s != '"' && *s != '\'')
			s++;
		(*count)++;
	}
	return (s - start);
}
