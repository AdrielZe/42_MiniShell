/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 15:46:10 by asilveir          #+#    #+#             */
/*   Updated: 2024/10/23 16:49:23 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*string_1;
	unsigned char	*string_2;
	size_t			i;

	string_1 = (unsigned char *) s1;
	string_2 = (unsigned char *)s2;
	i = 0;
	if (!n)
		return (0);
	while (i < n - 1)
	{
		if (*string_1 != *string_2)
			return (*string_1 - *string_2);
		string_1++;
		string_2++;
		i++;
	}
	return (*string_1 - *string_2);
}
