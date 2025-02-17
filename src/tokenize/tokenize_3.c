/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:49:40 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/17 01:21:56 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tokenize.h"
#include "../../headers/parsing.h"

char	*extract_quoted_word(char *quote, const char **start, const char **s)
{
	const char	*end;
	char		*word;

	*quote = **s;
	(*s)++;
	*start = *s;
	while (**s && **s != *quote)
		(*s)++;
	end = *s;
	if (**s == *quote)
		(*s)++;
	word = allocate_word(*start, end - *start);
	return (word);
}
