/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:59:58 by victda-s          #+#    #+#             */
/*   Updated: 2025/02/19 17:45:45 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tokenize.h"
#include "../../headers/parsing.h"

void	skip_spaces_and_alloc_elements(const char **s, char ***array, int *i)
{
	while (**s == ' ')
		(*s)++;
	if (**s == '\0')
		return ;
	alloc_pipe(s, array, i);
	alloc_append(s, array, i);
	alloc_outfile(s, array, i);
	alloc_heredoc(s, array, i);
	alloc_infile(s, array, i);
}

void	alloc_new_word_in_array(char ***array, int *i, char *new_word)
{
	(*array)[*i] = new_word;
	(*i)++;
}
int	is_command(char *s)
{
	if (s[0] == '"' || s[0] == '\'')
		return (0);
	return (1);
}
int should_merge_token(char **array, int i, int is_string, char *new_word)
{

    	if ((i > 0 && array && array[i - 1] && array[i - 1][0] != '|' &&
            array[i - 1][0] != '<' && array[i - 1][0] != '>' &&
            (array[i - 1][0] != '"' && array[i - 1][0] != '\'' && 
            new_word[0] != '"' && new_word[0] != '\'')) || is_string == 1) 
	{	
		printf("Realizou o merge!\n");
		merge_last_token(&array, i, new_word);
    	}
    	return 0;
}

char	*remove_quotes(const char *str)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	if ((str[0] == '"' || str[0] == '\'') && str[len - 1] == str[0] && len > 1)
	{
		new_str = ft_substr(str, 1, len - 2); // Remove primeira e última aspas
		return (new_str);
	}
	return (ft_strdup(str)); // Retorna cópia se não houver aspas
}

void	merge_last_token(char ***array, int i, char *new_word)
{
	char	*temp;
	char	*cleaned_last;
	char	*cleaned_new;
	char	*joined;

	// Remove aspas do último token e do novo token se necessário
	cleaned_last = remove_quotes((*array)[i - 1]);
	cleaned_new = remove_quotes(new_word);

	// Faz o join dos tokens limpos
	temp = ft_strjoin(cleaned_last, " ");
	joined = ft_strjoin(temp, cleaned_new);

	// Libera memória das strings temporárias
	free(temp);
	free(cleaned_last);
	free(cleaned_new);
	free((*array)[i - 1]);
	free(new_word);

	// Atualiza o último token no array
	(*array)[i - 1] = joined;
}
