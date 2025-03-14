/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:59:58 by victda-s          #+#    #+#             */
/*   Updated: 2025/02/27 21:24:19 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/parsing.h"
#include "../../headers/tokenize.h"

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

void	alloc_new_word_in_array(char ***array,
				int *i, char *new_word)
{
		(*array)[*i] = new_word;
		(*i)++;
	// *old_string = NULL;
}

int	should_merge_token(int is_string)
{
	if (is_string == 1)
		return (1);
	return (0);
}

void	merge_last_token(char ***array, int i, char *new_word)
{
	char	*temp;
	char	*joined;

	if (i <= 0 || !new_word || !(*array) || !(*array)[i - 1])
		return ;
	temp = ft_strjoin((*array)[i - 1], " ");
	if (!temp)
		return ;
	joined = ft_strjoin(temp, new_word);
	free(temp);
	if (!joined)
		return ;
	if ((*array)[i - 1])
	{
		free((*array)[i - 1]);
		(*array)[i - 1] = NULL;
	}
	(*array)[i - 1] = joined;
	//free(new_word);
}
