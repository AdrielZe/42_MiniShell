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

void	get_new_word(char **new_word, const char **s, char ***array)
{
	*new_word = process_quotes(s);
	if (!*new_word)
	{
		free_array(*array);
		exit(0);
	}
}

int	check_if_is_string(char *word)
{
	if ((ft_strlen(word) > 1 && ((word[0] == '\''
					&& word[ft_strlen(word) - 1] == '\'')
				|| (word[0] == '"'
					&& word[ft_strlen(word) - 1] == '"'))))
		return (0);
	return (1);
}

void	remove_quotes(char *str)
{
	char	*read;
	char	*write;

	read = str;
	write = str;
	if (!str)
		return ;
	while (*read)
	{
		if (*read != '"' && *read != '\'')
		{
			*write = *read;
			write++;
		}
		read++;
	}
	*write = '\0';
}

void	start_word_variables(t_word_data *data,
		char ***array, int *is_executable, int *i)
{
	data->old_string = NULL;
	data->is_executable = is_executable;
	data->i = i;
	data->array = array;
}

void	process_words(const char **s, char ***array, int *i, char **envp)
{
	char		*old_string;
	char		*new_word;
	static int	is_executable = 0;
	t_word_data	data;

	start_word_variables(&data, array, &is_executable, i);
	new_word = NULL;
	old_string = NULL;
	if (ft_exit(s, envp) == 1)
		return ;
	while (**s)
	{
		skip_spaces_and_alloc_elements(s, array, i);
		if (!**s)
			return ;
		get_new_word(&new_word, s, array);
		if (!new_word)
		{
			free_array(*array);
			return ;
		}
		process_new_word(new_word, &data);
		handle_word_quotes(new_word, &is_executable, envp, *i);
	}
	free(old_string);
}
