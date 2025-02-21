/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2025/01/15 12:36:14 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/24 13:58:31 by marvin           ###   ########.fr       */
/*   Updated: 2025/01/24 13:58:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tokenize.h"
#include <stdio.h>

int	count_if(size_t *count, const char *s)
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
		while (*s && *s != '|' && *s != '<'
			&& *s != '"' && *s != '\'' && *s != '>' && *s != '$')
			s++;
		(*count)++;
	}
	return (s - start);
}

void	clear_token_list(t_tokens **token_list)
{
	t_tokens	*current;
	t_tokens	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*token_list = NULL;
}

static void	create_tokens(char *token_value, t_tokens **token_list)
{
	// if (ft_strchr(token_value, '$') || (ft_strchr(token_value, '$')
	// 		&& (ft_strchr(token_value, '"'))))
	// 	append_token(token_list, TOKEN_ENV_VAR, token_value);
	if (ft_strcmp(token_value, ">>") == 0)
		append_token(token_list, TOKEN_APPEND, token_value);
	else if (ft_strcmp(token_value, "<<") == 0)
		append_token(token_list, TOKEN_HEREDOC, token_value);
	else if (ft_strcmp(token_value, ">") == 0)
		append_token(token_list, TOKEN_REDIRECT_OUT, token_value);
	else if (ft_strcmp(token_value, "<") == 0)
		append_token(token_list, TOKEN_REDIRECT_IN, token_value);
	else if (ft_strcmp(token_value, "|") == 0)
		append_token(token_list, TOKEN_PIPE, token_value);
	else if (token_value && ft_strlen(token_value) > 1 && (token_value[0] == '"'
			&& token_value[ft_strlen(token_value) - 1] == '"'
			|| token_value[0] == '\''
			&& token_value[ft_strlen(token_value) - 1] == '\''))
		append_token(token_list, TOKEN_WORD, token_value);
	else
		append_token(token_list, TOKEN_COMMAND, token_value);
}

void	classify_token(char **tokens, t_tokens **token_list)
{
	int	i;

	i = 0;
	clear_token_list(token_list);
	while (tokens[i])
	{
		create_tokens(tokens[i], token_list);
		i++;
	}
}
