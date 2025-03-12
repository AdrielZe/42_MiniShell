/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:47:35 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/12 14:48:20 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>

int	ft_isnumeric(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '-' || str[i] == '+') // Permite sinais no início
		i++;
	while (str[i])
	{
		if (!isdigit((unsigned char)str[i])) // Verifica se não é um número
			return (0);
		i++;
	}
	return (1);
}

