/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victda-s <victda-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:59:58 by victda-s          #+#    #+#             */
/*   Updated: 2025/02/12 18:05:11 by victda-s         ###   ########.fr       */
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
	alloc_infile(s, array, i);
	alloc_heredoc(s, array, i);
}

void	alloc_new_word_in_array(char ***array, int *i, char *new_word)
{
	(*array)[*i] = new_word;
	(*i)++;
}

int	should_merge_token(char **array, int i)
{
	return (i > 0 && array[i - 1] && array[i - 1][0] != '|' &&
			array[i - 1][0] != '<' && array[i - 1][0] != '>');
}

void	merge_last_token(char ***array, int i, char *new_word)
{
	char	*temp;
	char	*joined;

	temp = ft_strjoin((*array)[i - 1], " ");
	joined = ft_strjoin(temp, new_word);
	free(temp);
	free((*array)[i - 1]);
	free(new_word);
	(*array)[i - 1] = joined;
}
