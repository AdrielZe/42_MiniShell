/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:22:30 by asilveir          #+#    #+#             */
/*   Updated: 2024/10/22 23:13:55 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char const *str)
{
	char	*str_space;
	int		i;

	i = 0;
	str_space = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (str_space == NULL)
		return (NULL);
	while (str[i])
	{
		str_space[i] = str[i];
		i++;
	}
	str_space[i] = '\0';
	return (str_space);
}
