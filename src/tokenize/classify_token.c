/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:36:14 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/15 16:41:18 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tokenize.h"

int	count_if(size_t *count, const char *s, char c)
{
	const char	*start;
	char		quote;

	start = s;
	if (*s == '"' || *s == '\'')
	{
		quote = *s++;
		while (*s && *s != quote)
			s++;
		if (*s)
			s++;
		(*count)++;
	}
	else if (*s++ == '|')
		(*count)++;
	else
	{
		while (*s && *s != c && *s != '|' && *s != '"' && *s != '\'')
			s++;
		(*count)++;
	}
	return (s - start);
}

void	classify_token(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '$'))
		{
			// ENV_VAR
			printf("1");
		}
		else if (ft_strcmp(tokens[i], ">>") == 0)
		{
			// Redirecionamento de Saída (Anexar)
			printf("2");
		}
		else if (ft_strcmp(tokens[i], "<<") == 0)
		{
			// Here Document
			printf("3");
		}
		else if (ft_strcmp(tokens[i], ">") == 0)
		{
			// Redirecionamento de Saída
			printf("4");
		}
		else if (ft_strcmp(tokens[i], "<") == 0)
		{
			// Redirecionamento de Entrada
			printf("5");
		}
		else if (ft_strcmp(tokens[i], "|") == 0)
		{
			// PIPE
			printf("6");
		}
		else
		{
			// word
			printf("7");
		}
		i++;
	}
}
