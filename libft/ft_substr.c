/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:46:49 by asilveir          #+#    #+#             */
/*   Updated: 2024/10/23 17:36:57 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	check_len(size_t len, size_t strlen, unsigned int start)
{
	if (len > strlen - start)
	{
		len = strlen - start;
		return (len);
	}
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{	
	char	*substr;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substr = (char *)malloc((1) * sizeof(char));
		substr[0] = '\0';
		return (substr);
	}
	len = check_len(len, ft_strlen(s), start);
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
