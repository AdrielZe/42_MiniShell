/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:29:27 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/20 20:18:19 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	count_words(const char *s)
{
	int		count;
	int		in_quotes;
	char	quote_char;

	count = 0;
	in_quotes = 0;
	quote_char = 0;
	while (*s)
	{
		while (is_space(*s))
			s++;
		if (*s == '\0')
			break ;
		if (*s == '"' || *s == '\'')
		{
			quote_char = *s++;
			in_quotes = 1;
			while (*s && (*s != quote_char))
				s++;
			if (*s == quote_char)
				s++;
		}
		else
		{
			while (*s && !is_space(*s) && *s != '"' && *s != '\'')
				s++;
		}
		count++;
	}
	return (count);
}

char	*extract_word(const char **s)
{
	char		*word;
	int			len;
	int			in_quotes;
	char		quote_char;
	const char	*start = *s;

	len = 0;
	in_quotes = 0;
	quote_char = 0;
	if (**s == '"' || **s == '\'')
	{
		quote_char = **s;
		start++;
		(*s)++;
		in_quotes = 1;
		while (**s && **s != quote_char)
		{
			(*s)++;
			len++;
		}
		if (**s == quote_char)
			(*s)++;
	}
	else
	{
		while (**s && !is_space(**s) && **s != '"' && **s != '\'')
		{
			(*s)++;
			len++;
		}
	}
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	strncpy(word, start, len);
	word[len] = '\0';
	return (word);
}

char	**split_with_quotes(const char *s)
{
	int		i;
	char	**result;
	int		words;

	i = 0;
	words = count_words(s);
	result = (char **)malloc((words + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (*s)
	{
		while (is_space(*s))
			s++;
		if (*s == '\0')
			break ;
		result[i++] = extract_word(&s);
	}
	result[i] = NULL;
	return (result);
}
