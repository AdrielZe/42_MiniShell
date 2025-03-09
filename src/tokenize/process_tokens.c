/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:22:50 by marvin            #+#    #+#             */
/*   Updated: 2025/03/08 21:22:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

void	handle_word_quotes(char *new_word,
				int *is_executable, char **envp, int index)
{
	char	*unquoted_word;

	if (!new_word)
		return ;
	unquoted_word = ft_strdup(new_word);
	if (!unquoted_word)
		return ;
	remove_quotes(unquoted_word);
	if (search_valid_path(unquoted_word, envp) != NULL && index != 0)
		*is_executable = 1;
	free(unquoted_word);
}

void	process_new_word(char *new_word, t_word_data *data)
{
	int	is_string;

	is_string = 0;
	check_if_is_string(new_word, data->old_string, &is_string);
	if (*(data->i) == 0)
	{
		alloc_new_word_in_array(data->array,
			data->i, new_word, data->old_string);
		is_string = 0;
	}
	else if (should_merge_token(is_string) == 1 || *(data->is_executable) == 1)
	{
		merge_last_token(data->array, *(data->i), new_word);
		is_string = 0;
		*(data->is_executable) = 0;
		data->old_string = NULL;
	}
	else
		alloc_new_word_in_array(data->array, data->i,
			new_word, data->old_string);
}
