/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:38:36 by asilveir          #+#    #+#             */
/*   Updated: 2024/10/23 17:23:55 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	unsigned char	ch;
	int				i;

	ch = (unsigned char) c;
	i = 0;
	while ((*s))
	{
		s++;
		i++;
	}
	while (i >= 0)
	{
		if (*s == ch)
		{
			return ((char *) s);
		}
		s--;
		i--;
	}
	if (ch == '\0')
		return ((char *) s);
	return (NULL);
}
