/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:49:40 by asilveir          #+#    #+#             */
/*   Updated: 2025/02/27 21:22:26 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tokenize.h"
#include "../../headers/parsing.h"

static void	get_new_word(char **new_word, const char **s, char ***array, int *i)
{
	*new_word = process_quotes(s);
	if (!*new_word)
	{
		free_array(*array, *i);
		exit(0);
	}
}

void	print_array(char **array)
{
	int	j;

	j = 0;
	printf("Array atual:\n");
	if (!array)
	{
		printf("Array é NULL\n");
		return ;
	}
	while (array[j])
	{
		printf("[%d] %s\n", j, array[j]);
		j++;
	}
	printf("\n");
}

void	check_if_is_string(char *new_word,
			char **old_string, int *is_string, int len)
{
	if ((new_word[0] == '"' || new_word[0] == '\'')
		&& new_word[len - 1] == new_word[0] && len > 1
		&& (*old_string != NULL && *old_string[0] != '"'))
	{
		*is_string = 1;
		*old_string = NULL;
	}
}

void	process_words(const char **s, char ***array, int *i)
{
	static char	*old_string = NULL;
	char		*new_word;
	int			is_string;
	int			len;

	is_string = 0;
	while (**s)
	{
		skip_spaces_and_alloc_elements(s, array, i);
		if (*s == NULL)
			break ;
		get_new_word(&new_word, s, array, i);
		len = ft_strlen(new_word);
		if (old_string)
			free(old_string);
		if (!old_string)
			old_string = ft_strdup(new_word);
		check_if_is_string(new_word, &old_string, &is_string, len);
		if (should_merge_token(*array, *i, is_string) == 1)
		{
			merge_last_token(array, *i, new_word);
			is_string = 0;
			free(old_string);
			old_string = NULL;
		}
		else
		{
			free(old_string);
			alloc_new_word_in_array(array, i, new_word, &old_string);
		}
	}
}
