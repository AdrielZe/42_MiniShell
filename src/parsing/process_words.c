/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_words.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:38:29 by marvin            #+#    #+#             */
/*   Updated: 2025/03/08 18:38:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

char	*extract_new_word(const char **s, char ***array, int *i)
{
	char	*new_word;

	new_word = NULL;
	get_new_word(&new_word, s, array, i);
	if (!new_word)
	{
		free_array(*array, array_len(*array));
		return (NULL);
	}
	return (new_word);
}

void	handle_word(char *new_word, char **old_string,
			char ***array, int *i, int *is_executable, char **envp)
{
	int		is_string;
	char	*unquoted_word;

	is_string = 0;
	unquoted_word = NULL;
	check_if_is_string(new_word, old_string, &is_string);
	if (*i == 0)
	{
		alloc_new_word_in_array(array, i, new_word, old_string);
		is_string = 0;
	}
	else if (should_merge_token(is_string) == 1 || *is_executable == 1)
	{
		merge_last_token(array, *i, new_word);
		is_string = 0;
		*is_executable = 0;
		*old_string = NULL;
	}
	else
		alloc_new_word_in_array(array, i, new_word, old_string);
	unquoted_word = ft_strdup(new_word);
	if (!unquoted_word)
		return ;
	remove_quotes(unquoted_word);
	if (search_valid_path(unquoted_word, envp) != NULL && *i != 0)
		*is_executable = 1;
	free(unquoted_word);
}
