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

void	alloc_heredoc(const char **s, char ***array, int *i)
{
	if (**s == '<' && (*s)[1] == '<')
	{
		(*array)[(*i)++] = ft_strdup("<<");
		*s += 2;
	}
}

void	alloc_append(const char **s, char ***array, int *i)
{
	if (**s == '>' && (*s)[1] == '>')
	{
		(*array)[(*i)++] = ft_strdup(">>");
		*s += 2;
	}
}

void	alloc_pipe(const char **s, char ***array, int *i)
{
	if (**s == '|')
	{
		(*array)[(*i)] = ft_strdup("|");
		(*s)++;
	}
}

void	alloc_outfile(const char **s, char ***array, int *i)
{
	if (**s == '>')
	{
		(*array)[(*i)++] = ft_strdup(">");
		(*s)++;
	}
}

void	alloc_infile(const char **s, char ***array, int *i)
{
	if (**s == '<')
	{
		(*array)[(*i)++] = ft_strdup("<");
		(*s)++;
	}
}
