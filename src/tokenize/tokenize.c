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
	{
		free(word);
		return (NULL);
	}
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
		while (*s == '|' || (*s == '<' && *(s + 1) == '<'))
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

static char	*process_quotes(const char **s)
{
	const char	*start;
	char		quote;
	char		*extracted_word;

	if (**s == '"' || **s == '\'')
	{
		quote = **s;
		extracted_word = extract_quoted_word(&quote, &start, s);
		if (!extracted_word)
			return (NULL);
		return (extracted_word);
	}
	else
	{
		start = *s;
		while (**s && **s != ' ' && **s != '|' && **s != '<' && **s != '>')
			(*s)++;
		return (allocate_word(start, *s - start));
	}
}

char	**tokenize(const char *s)
{
	int		i;
	char	**array;
	char	*new_word;

	i = 0;
	array = malloc((ft_count_word(s) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (*s)
	{
		skip_spaces_and_alloc_elements(&s, &array, &i);
		if (*s == '\0')
			break ;
		new_word = process_quotes(&s);
		if (!new_word)
			return (free_array(array, i), NULL);
		if (should_merge_token(array, i))
			merge_last_token(&array, i, new_word);
		else
			alloc_new_word_in_array(&array, &i, new_word);
	}
	array[i] = NULL;
	return (array);
}
