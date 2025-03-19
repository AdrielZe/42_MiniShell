/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:17:56 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/24 14:05:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

static char	*find_string_to_replace(char *input, int index_of_env_symbol)
{
	char	*word_to_switch;
	int		start;
	int		end;
	int		temp;
	int		i;

	i = 0;
	start = index_of_env_symbol + 1;
	if (input[start] == '?')
		return (ft_strdup("?"));
	end = start;
	while (isalnum(input[end]) || input[end] == '_')
		end++;
	word_to_switch = (char *)calloc((end - start + 1), sizeof(char));
	if (!word_to_switch)
		return (NULL);
	temp = start;
	while (temp < end)
		word_to_switch[i++] = input[temp++];
	word_to_switch[i] = '\0';
	return (word_to_switch);
}

int	is_only_slash(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str != '/' && *str != ' ')
			return (1);
		str++;
	}
	return (0);
}

int	is_only_dollar(const char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (*str != '$' && *str != ' ')
			return (1);
		str++;
	}
	return (0);
}

char	*replace_env_var(char *input, int *index, int is_heredoc)
{
	char	*original_input;
	char	*word_to_switch;
	char	*input_to_return;

	original_input = input;
	word_to_switch = find_string_to_replace(input, *index);
	if (!word_to_switch)
		return (input);
	input_to_return = replace_substring(input, word_to_switch, *index);
	if (!input_to_return)
	{
		free(word_to_switch);
		return (input);
	}
	if (original_input != input_to_return)
		free(original_input);
	free(word_to_switch);
	return (input_to_return);
}

char	*process_env_var(char *input, int is_heredoc)
{
	int		index;
	int		in_single_quotes;
	int		new_len;

	index = 0;
	in_single_quotes = 0;
	if (!input || is_only_dollar(input) == 0)
		return (input);
	while (input[index])
	{
		if (input[index] == '\'')
			in_single_quotes = !in_single_quotes;
		if ((input[index] == '$' && !in_single_quotes)
			|| (input[index] == '$' && is_heredoc == 1))
		{
			input = replace_env_var(input, &index, is_heredoc);
			new_len = ft_strlen(input);
			if (index >= new_len)
				break ;
		}
		index++;
	}
	return (input);
}
