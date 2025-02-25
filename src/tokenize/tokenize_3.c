/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:49:40 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/24 21:32:09 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tokenize.h"
#include "../../headers/parsing.h"

static void	get_new_word(char **new_word, const char **s, char ***array, int *i)
{
	*new_word = process_quotes(s);
	if (!new_word)
	{
		free_array(*array, *i);
		exit(0);
	}
}

void	process_words(const char **s, char ***array, int *i)
{
	int		is_string;
	int		len;
	char	*new_word;

	is_string = 0;
	while (**s)
	{
		skip_spaces_and_alloc_elements(s, array, i);
		if (*s == NULL)
			break ;
		get_new_word(&new_word, s, array, i);
		len = ft_strlen(new_word);
		if ((new_word[0] == '"' || new_word[0] == '\'')
			&& new_word[len - 1] == new_word[0] && len > 1)
			is_string = 1;
		if (should_merge_token(*array, *i, is_string, new_word) == 1)
		{
			merge_last_token(array, *i, new_word);
			is_string = 0;
		}
		else
		{
			printf("In alloc new word\n");
			alloc_new_word_in_array(array, i, new_word);
		}
	}
}
