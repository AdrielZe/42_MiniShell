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
    int i2 = 0;
    if (!array)
        return;
    
    while (array[i2])
    {
        free(array[i2]);
        i2++;
    }
    free(array);
}

char	*allocate_word(const char *s, int len)
{
	char	*word;

	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	memcpy(word, s, len);
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
			s++;
			if (*s)
				s++;
		}
		count++;
	}
	return (count + delim_counter);
}

char	*process_quotes(const char **s)
{
	const char	*start;
	char		quote;

	start = *s;
	if (**s == '"' || **s == '\'')
	{
		quote = *(*s)++;
		while (**s && **s != quote)
			(*s)++;
		if (**s == quote)
			(*s)++;
	}
	else if (**s == '|')
		(*s)++;
	else
	{
		while (**s && **s != '|' && **s != '<' && **s != '>'
			&& **s != '"' && **s != '\'')
			(*s)++;
	}
	return (allocate_word(start, *s - start));
}

char	**tokenize(const char *s, char **envp)
{
	char	**array;
	int		i;

	while(*s && *s == ' ')
		*s++;
	if (s == NULL || ft_count_word(s) == 0)
		return (NULL);
	i = 0;
	array = malloc((ft_count_word(s) + 1) * sizeof(char *));
	if (control_quotes(s) == 1)
		return (NULL);
	if (!array)
		return (NULL);
	process_words(&s, &array, &i, envp);
	array[i] = NULL;
	return (array);
}
