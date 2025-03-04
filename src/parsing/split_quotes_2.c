/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:29:27 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/26 23:11:28 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	skip_quotes(char *quote_char, char **s)
{
	*quote_char = **s;
	(*s)++;
	while (**s && **s != *quote_char)
		(*s)++;
	if (**s == *quote_char)
		(*s)++;
}

static void	count_unquoted_word_length(char **s, int *len)
{
	while (**s && !is_space(**s) && **s != '"' && **s != '\'')
	{
		(*s)++;
		(*len)++;
	}
}

static void	count_word_len_split(char **s, int *len)
{
	char	quote_char;

	quote_char = 0;
	if (**s == '"' || **s == '\'')
	{
		skip_quotes(&quote_char, s);
		(*len)++;
	}
	else
		count_unquoted_word_length(s, len);
}

int	get_word_length(char **s, int *len, int *in_quotes, char *quote_char)
{
	*len = 0;
	*in_quotes = 0;
	*quote_char = 0;
	if (**s == '"' || **s == '\'')
	{
		*quote_char = **s;
		(*s)++;
		*in_quotes = 1;
		while (**s && **s != *quote_char)
		{
			(*s)++;
			(*len)++;
		}
		if (**s == *quote_char)
			(*s)++;
	}
	else
		count_word_len_split(s, len);
	return (*len);
}
