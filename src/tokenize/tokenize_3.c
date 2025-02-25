/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:49:40 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/25 00:01:29 by asilveir         ###   ########.fr       */
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

void	print_array(char **array)
{
	int j = 0;

	printf("Array atual:\n");
	if (!array)
	{
		printf("Array é NULL\n");
		return;
	}
	while (array[j])
	{
		printf("[%d] %s\n", j, array[j]);
		j++;
	}
	printf("\n");
}

void	process_words(const char **s, char ***array, int *i)
{
	int		is_string;
	static char *old_string;
	int		len;
	char	*new_word;

	is_string = 0;
	if (!old_string)
		old_string = NULL;
	while (**s)
	{
		if (!old_string)
			old_string = ft_strdup(*s);
		printf("Old string: %s\n", old_string);
		skip_spaces_and_alloc_elements(s, array, i);
		if (*s == NULL)
			break ;
		get_new_word(&new_word, s, array, i);
		len = ft_strlen(new_word);
		if ((new_word[0] == '"' || new_word[0] == '\'')
			&& new_word[len - 1] == new_word[0] && len > 1 && (old_string != NULL && old_string[0] != '"'))
		{
			is_string = 1;
			old_string = NULL;
		}
		if (should_merge_token(*array, *i, is_string, new_word) == 1)
		{
			merge_last_token(array, *i, new_word);
			is_string = 0;
		}
		else
		{
			alloc_new_word_in_array(array, i, new_word);
			old_string = NULL;
		}
	}
}
