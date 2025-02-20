/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 18:29:27 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/20 17:47:06 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	skip_quotes(char *quote_char, const char **s)
{
	*quote_char = **s;
	(*s)++;
	while (**s && **s != *quote_char)
		(*s)++;
	if (**s == *quote_char)
		(*s)++;
}

void	count_unquoted_word_length(const char **s, int *len)
{
	while (**s && !is_space(**s) && **s != '"' && **s != '\'')
	{
		(*s)++;
		(*len)++;
	}
}

void 	count_word_len_split(const char **s, int *len)
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

