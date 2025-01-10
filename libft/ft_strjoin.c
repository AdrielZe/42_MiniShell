/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:46:43 by asilveir          #+#    #+#             */
/*   Updated: 2024/12/17 18:38:26 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *str1, char *str2)
{
	char		*concat_string;
	size_t		i;
	size_t		j;

	if (!str1)
	{
		str1 = malloc(sizeof(char));
		str1[0] = '\0';
	}
	concat_string = malloc(((ft_strlen(str1) + ft_strlen(str2)) + 1));
	if (!concat_string)
		return (NULL);
	i = 0;
	j = 0;
	while (str1[i])
	{
		concat_string[i] = str1[i];
		i++;
	}
	while (str2[j])
		concat_string[i++] = str2[j++];
	concat_string[i] = '\0';
	return (concat_string);
}
