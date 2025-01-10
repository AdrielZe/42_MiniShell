/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:54:42 by asilveir          #+#    #+#             */
/*   Updated: 2024/12/04 18:25:49 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *s, int c)
{
	int		i;
	char	*string_to_search_in;

	if (!s || !c)
		return (NULL);
	i = 0;
	string_to_search_in = (char *)s;
	while (string_to_search_in[i])
	{
		if (string_to_search_in[i] == (char) c)
			return (&string_to_search_in[i]);
		i++;
	}
	return (0);
}

int	ft_endl(char	*buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		return (1);
	return (0);
}
