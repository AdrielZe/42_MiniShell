/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 12:12:24 by victda-s          #+#    #+#             */
/*   Updated: 2025/01/24 14:04:23 by marvin           ###   ########.fr       */
/*   Updated: 2025/01/24 14:04:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include <stdlib.h>
# include "parsing.h" 

typedef enum e_token_typeh
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

t_tokens	*get_token_by_index(t_tokens *token_list, int index);
void		append_token(t_tokens **token_list, t_token_type type, char *value);
void		print_list(t_tokens *token_list);
void		classify_token(char **tokens, t_tokens **token_list);
void		clear_token_list(t_tokens **token_list);
void		free_array(char **array, int i);
void		echo(t_tokens *tokens);
char		*allocate_word(const char *s, int len);
char		*extract_quoted_word(char *quote,
				const char **start, const char **s);
void		append_token(t_tokens **token_list, t_token_type type, char *value);
void		print_list(t_tokens *token_list);
void		skip_spaces_and_alloc_elements(const char **s,
				char ***array, int *i);
void		alloc_new_word_in_array(char ***array, int *i, char *new_word);
void		free_elements(char ***array, int i, char **temp, char **new_word);
void		merge_last_token(char ***array, int i, char *new_word);
void		classify_token(char **tokens, t_tokens **token_list);
void		clear_token_list(t_tokens **token_list);
void		free_array(char **array, int i);
void		echo(t_tokens *tokens);
char		**tokenize(const char *s);
void		alloc_pipe(const char **s, char ***array, int *i);
void		alloc_outfile(const char **s, char ***array, int *i);
void		alloc_append(const char **s, char ***array, int *i);
size_t		ft_count_word(const char *s);
void		alloc_heredoc(const char **s, char ***array, int *i);
void		alloc_infile(const char **s, char ***array, int *i);
int			count_if(size_t *count, const char *s);
int			should_merge_token(char **array, int i,
				int is_string, char *new_word);
int			malloc_array(char ***array, const char *s);

#endif