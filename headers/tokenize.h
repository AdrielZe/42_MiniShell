/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:12:24 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/21 15:01:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "../headers/main.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_COMMAND,
}	t_token_type;

typedef struct s_tokens
{
	t_token_type	type;
	char			*value;
	struct s_tokens	*next;
}	t_tokens;

int		count_if(size_t *count, const char *s, char c);
void	append_token(t_tokens **token_list, t_token_type type, char *value);
void	print_list(t_tokens *token_list);
char	**tokenize(const char *s, char c);
char	*get_token_by_index(t_tokens *token_list, int index);
void	classify_token(char **tokens, t_tokens **token_list);
void	clear_token_list(t_tokens **token_list);
void	free_array(char **array, int i);

#endif