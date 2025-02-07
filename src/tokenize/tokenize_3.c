/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:49:40 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/07 17:06:10 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tokenize.h"
#include "../../headers/parsing.h"

char	*extract_quoted_word(char *quote, const char **start, const char **s)
{
	*quote = **s;
	*start = (*s)++;
	while (**s && **s != *quote)
		(*s)++;
	if (**s)
		(*s)++;
	return (allocate_word(*start, *s - *start));
}
