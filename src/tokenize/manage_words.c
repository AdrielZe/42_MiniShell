/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_words.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:17:06 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/19 09:21:04 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

char	*allocate_word(const char *s, int len)
{
	char	*word;

	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_memcpy(word, s, len);
	word[len] = '\0';
	return (word);
}

size_t	ft_count_word(const char *s)
{
	size_t	count;
	size_t	delim_counter;

	delim_counter = 0;
	count = 0;
	while (*s)
	{
		s += count_if(&count, s);
		while (*s == '|')
		{
			delim_counter++;
			if (*s)
				s++;
		}
		count++;
	}
	return (count + delim_counter);
}
