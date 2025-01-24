/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:17:14 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/24 14:00:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_array_split(char **array, int i)
{
	while (i > 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
}

char	*allocate_word_split(const char *s, char c)
{
	char	*word;
	int		i;
	int		temp;

	temp = 0;
	i = 0;
	while (*s != c && *s)
	{
		i++;
		s++;
	}
	s -= i;
	word = malloc((i + 1) * sizeof(char));
	if (!word)
		return (NULL);
	temp = i;
	i = 0;
	while (i < temp)
	{
		word[i] = *s;
		i++;
		s++;
	}
	word[i] = '\0';
	return (word);
}

size_t	ft_count_word_split(char *s, char c)
{
	size_t	i;
	int		in_word;

	i = 0;
	in_word = 0;
	while (*s)
	{
		if ((*s != c) && (in_word == 0))
		{
			in_word = 1;
			i++;
		}
		if (*s == c)
			in_word = 0;
		s++;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;

	i = 0;
	array = (char **)malloc((ft_count_word_split((char *)s, c)
				+ 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			array[i] = allocate_word_split(s, c);
			if (!array[i])
				free_array_split(array, i);
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	array[i] = NULL;
	return (array);
}
