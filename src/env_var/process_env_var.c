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

static char	*replace_substring(char *string, char *replace_string, int index)
{
	char	*string_rest;
	char	*env_value;
	char	*new_string;
	int		new_length;

	string_rest = ft_substr(string, index + ft_strlen(replace_string) + 1,
			ft_strlen(string) - index);
	if (!string_rest)
		return (string);
	if (ft_strcmp(replace_string, "?") == 0)
		env_value = getenv("EXITCODEMINISHELL");
	else
		env_value = getenv(replace_string);
	if (!env_value)
		env_value = "";
	new_length = index + ft_strlen(env_value) + ft_strlen(string_rest) + 1;
	new_string = malloc(new_length);
	if (!new_string)
		return (string);
	ft_strlcpy(new_string, string, index + 1);
	ft_strlcat(new_string, env_value, new_length);
	ft_strlcat(new_string, string_rest, new_length);
	free(string_rest);
	return (new_string);
}

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

char	*process_env_var(char *input, int is_heredoc)
{
	char	*input_to_return;
	char	*original_input;
	char	*word_to_switch;
	int		index;
	int		in_single_quotes;

	index = 0;
	in_single_quotes = 0;
	if (!input || is_only_dollar(input) == 0)
		return (input);
	while (input[index])
	{
		if (input[index] == '\'')
			in_single_quotes = !in_single_quotes;
		if ((input[index] == '$' && !in_single_quotes) || (input[index] == '$' && is_heredoc == 1))
		{
			original_input = input;
			word_to_switch = find_string_to_replace(input, index);
			if (!word_to_switch)
				return (input) ;
			input_to_return = replace_substring(input, word_to_switch, index);
			if (!input_to_return)
			{
				free(word_to_switch);
				return (input); // Error handling
            		}
			if (original_input != input_to_return)
				free(original_input);
			input = input_to_return;
			free(word_to_switch);

			int new_len = ft_strlen(input);
            if (index >= new_len)
                break;
		}
		index++;
	}
	return (input);
}
