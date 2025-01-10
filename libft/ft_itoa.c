/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 01:34:37 by asilveir          #+#    #+#             */
/*   Updated: 2024/10/23 17:06:22 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_digits(int n)
{
	size_t	i;

	i = 1;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*string;
	long	num;
	int		number_of_digits;
	int		is_negative;

	num = n;
	is_negative = 0;
	if (num < 0)
	{
		num = -num;
		is_negative = 1;
	}
	number_of_digits = count_digits(n) + is_negative;
	string = malloc((number_of_digits + 1) * sizeof(char));
	if (!string)
		return (NULL);
	string[number_of_digits] = '\0';
	while (number_of_digits--)
	{
		string[number_of_digits] = num % 10 + '0';
		num /= 10;
	}
	if (is_negative == 1)
		string[0] = '-';
	return (string);
}
