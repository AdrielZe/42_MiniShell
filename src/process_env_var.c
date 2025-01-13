/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asilveir <asilveir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 10:17:56 by asilveir          #+#    #+#             */
/*   Updated: 2025/01/13 15:14:32 by asilveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/main.h"

static char	*replace_substring(char *string, char *replace_string, int index)
{
	char	*string_rest;
	char	*env_value;
	int		i;

	i = 0;
	string_rest = ft_substr(string, index + ft_strlen(replace_string) + 1,
			ft_strlen(string) - index);
	if (!string_rest)
		return (string);
	env_value = getenv(replace_string);
	if (!env_value)
		return (string);
	while (env_value[i])
	{
		string[index] = env_value[i];
		index++;
		i++;
	}
	string[index] = '\0';
	string = ft_strjoin(string, string_rest);
	if (!string)
		return (string);
	free(string_rest);
	return (string);
}

static char	*find_string_to_replace(char *input, int index_of_env_symbol, int i)
{
	int		start;
	int		end;
	int		temp;
	char	*word_to_switch;

	start = index_of_env_symbol + 1;
	end = start;
	while (ft_isalnum(input[end]) || input[end] == '_')
		end++;
	word_to_switch = ft_calloc((end - start + 1), sizeof(char));
	if (!word_to_switch)
		return (NULL);
	temp = start;
	while (temp < end)
	{
		word_to_switch[i] = input[temp];
		temp++;
		i++;
	}
	word_to_switch[i] = '\0';
	return (word_to_switch);
}

char	*process_env_var(char *input)
{
	int		index_of_env_symbol;
	int		i;
	char	*input_to_return;
	char	*word_to_switch;

	index_of_env_symbol = 0;
	i = 0;
	while (input[index_of_env_symbol])
	{
		if (input[index_of_env_symbol] == '$')
		{
			word_to_switch = find_string_to_replace(input,
					index_of_env_symbol, i);
			input_to_return = replace_substring(input,
					word_to_switch, index_of_env_symbol);
			input = input_to_return;
			free(word_to_switch);
		}
		index_of_env_symbol++;
		i = 0;
	}
	return (input);
}
