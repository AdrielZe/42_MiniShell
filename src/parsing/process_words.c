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

char	*extract_new_word(const char **s, char ***array)
{
	char	*new_word;

	new_word = NULL;
	get_new_word(&new_word, s, array);
	if (!new_word)
	{
		free_array(*array);
		return (NULL);
	}
	return (new_word);
}

void	check_if_is_executable(char *new_word, char **envp,
				int *i, int *is_executable)
{
	char	*unquoted_word;

	unquoted_word = ft_strdup(new_word);
	if (!unquoted_word)
		return ;
	remove_quotes(unquoted_word);
	if (search_valid_path(unquoted_word, envp) != NULL && *i != 0)
		*is_executable = 1;
	free(unquoted_word);
}
