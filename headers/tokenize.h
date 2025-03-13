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
	TOKEN_SIMPLE_QUOTE,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_COMMAND,
}	t_token_type;

typedef struct s_word_data
{
	char	**old_string;
	int		*is_executable;
	int		*i;
	char	***array;
}	t_word_data;

typedef struct s_tokens
{
	t_token_type	type;
	char			*value;
	struct s_tokens	*next;
}	t_tokens;

//Função print_list não está sendo usada
// mas será útil para debugar (remover qnd projeto estiver pronto)

//src/tokenize/classify_token.c
int			count_if(size_t *count, const char *s);
void		clear_token_list(t_tokens **token_list);
void		classify_token(char **tokens, t_tokens **token_list);

//src/tokenize/tokenization_linked_list.c
void		append_token(t_tokens **token_list, t_token_type type, char *value);
void		print_list(t_tokens *token_list);

//src/tokenize/tokenize_1.c
void		free_array(char **array);
char		*allocate_word(const char *s, int len);
size_t		ft_count_word(const char *s);
char		*process_quotes(const char **s);
char		**tokenize(const char *s, char **envp);

//src/tokenize/tokenize_2.c
void		skip_spaces_and_alloc_elements(const char **s,
				char ***array, int *i);
void		alloc_new_word_in_array(char ***array, int *i,
				char *new_word);
int			should_merge_token(int is_string);
void		merge_last_token(char ***array, int i, char *new_word);

//src/tokenize/tokenize_3.c
void		process_words(const char **s, char ***array, int *i, char **envp);

//src/tokenize/tokenize_alloc_tokens.c
void		alloc_heredoc(const char **s, char ***array, int *i);
void		alloc_append(const char **s, char ***array, int *i);
void		alloc_pipe(const char **s, char ***array, int *i);
void		alloc_outfile(const char **s, char ***array, int *i);
void		alloc_infile(const char **s, char ***array, int *i);

void		handle_word_quotes(char *new_word, int *is_executable, char **envp, int index);
void		process_new_word(char *new_word, t_word_data *data);
void		set_word_data(t_word_data *data, char *old_string, int is_executable, int *i);
int		control_quotes(const char *new_word);
int		check_if_is_string(char *word);

#endif