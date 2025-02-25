/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:29:27 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/25 14:42:49 by asilveir         ###   ########.fr       */
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

static int	count_words(char *s)
{
	char	quote_char;
	int		count;
	int		in_quotes;

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
			skip_quotes(&quote_char, &s);
		else
		{
			while (*s && !is_space(*s) && *s != '"' && *s != '\'')
				s++;
		}
		count++;
	}
	return (count);
}

char	*extract_word(char **s)
{
	const char	*start;
	char		*word;
	char		quote_char;
	int			len;
	int			in_quotes;

	start = *s;
	get_word_length(s, &len, &in_quotes, &quote_char);
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	if (in_quotes == 1)
		ft_strncpy(word, start + (1), len);
	else
		ft_strncpy(word, start, len);
	word[len] = '\0';
	return (word);
}

char	**split_with_quotes(char *s)
{
	char	**result;
	int		i;
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
