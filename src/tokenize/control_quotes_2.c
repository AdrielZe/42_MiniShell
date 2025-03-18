/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_quotes_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 18:51:55 by asilveir          #+#    #+#             */
/*   Updated: 2025/03/18 00:30:35 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

char	*extract_quoted(const char **s, char quote)
{
	const char	*start;
	char		*word;

	start = *s;
	word = NULL;
	while (**s && **s != quote)
		(*s)++;
	if (**s == quote)
	{
		word = allocate_word(start, *s - start);
		(*s)++;
	}
	return (word);
}

char	*extract_unquoted(const char **s)
{
	const char	*start;

	start = *s;
	while (**s && !ft_strchr(" |<>", **s)
		&& **s != '"' && **s != '\'')
		(*s)++;
	return (allocate_word(start, *s - start));
}

char	*merge_words(char *word, char *temp)
{
	char	*joined;

	joined = ft_strjoin(word, temp);
	free(temp);
	free(word);
	return (joined);
}

char	*process_segment(const char **s)
{
	char	*temp;
	char	quote;

	temp = NULL;
	if (**s == '"' || **s == '\'')
	{
		quote = *(*s)++;
		temp = extract_quoted(s, quote);
	}
	else
		temp = extract_unquoted(s);
	return (temp);
}

char	*process_quotes(const char **s)
{
	char	*word;
	char	*temp;
	int		quotes;

	word = NULL;
	temp = NULL;
	quotes = is_quoted(*s);
	word = process_segment(s);
	while (**s && !ft_strchr(" |<>", **s))
	{
		temp = process_segment(s);
		word = merge_words(word, temp);
	}
	if (quotes != 0)
		add_quote_type(&word, quotes);
	return (word);
}
