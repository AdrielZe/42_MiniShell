/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:36:14 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/15 21:08:39 by victda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tokenize.h"
#include <stdio.h>

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

void	classify_token(char **tokens, t_tokens *token_list)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '$') || (ft_strchr(tokens[i], '$')
				&& (ft_strchr(tokens[i], '"'))))
			append_token(&token_list, TOKEN_ENV_VAR, tokens[i]);
		else if (ft_strcmp(tokens[i], ">>") == 0)
			append_token(&token_list, TOKEN_APPEND, tokens[i]);
		else if (ft_strcmp(tokens[i], "<<") == 0)
			append_token(&token_list, TOKEN_HEREDOC, tokens[i]);
		else if (ft_strcmp(tokens[i], ">") == 0)
			append_token(&token_list, TOKEN_REDIRECT_OUT, tokens[i]);
		else if (ft_strcmp(tokens[i], "<") == 0)
			append_token(&token_list, TOKEN_REDIRECT_IN, tokens[i]);
		else if (ft_strcmp(tokens[i], "|") == 0)
			append_token(&token_list, TOKEN_PIPE, tokens[i]);
		else
			append_token(&token_list, TOKEN_WORD, tokens[i]);
		i++;
	}
	print_list(token_list);
}
