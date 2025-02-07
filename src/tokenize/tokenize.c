/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:59:58 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/29 16:03:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tokenize.h"
#include "../../headers/parsing.h"

void	free_array(char **array, int i)
{
	if (!array)
		return ;
	while (i-- > 0)
	{
		if (array[i])
			free(array[i]);
	}
	free(array); 
}

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
		while (*s == '|' || (*s == '<' && *s++ == '<'))
		{
			delim_counter++;
			s++;
		}
              count++;
	}
	return (count + delim_counter);
}

static char *process_quotes(const char **s)
{
	const char	*start;
	char	quote;
	int	is_delim;
	int	i;

	if (**s == '"' || **s == '\'')
	{
		quote = **s;
		start = (*s)++;
		while (**s && **s != quote)
			(*s)++;
		if (**s)
			(*s)++;
		return (allocate_word(start, *s - start));
	}
	else
	{
		start = *s;
		while (**s)
		{
			is_delim = 0;
			i = 0;
			if (**s == '|' || (**s == '<' && *(*s + 1) == '<'))
			{
				is_delim = 1;
				break;
			}
				i++;
			if (is_delim || **s == '"' || **s == '\'')
				break;
			(*s)++;
       	 }
        return (allocate_word(start, *s - start));
    }
}

char	**tokenize(const char *s)
{
	int		i;
	char	**array;

	i = 0;
	array = malloc((ft_count_word(s) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (*s)
	{
		while (*s == ' ')
			s++;
		alloc_pipe(&s, &array, &i);
		alloc_heredoc(&s, &array, &i);
		array[i] = process_quotes(&s);
		if (!array[i])
			return (free_array(array, i), (NULL));
		i++;
	}
	array[i] = NULL;
	return (array);
}
